#pragma once

#include "support/winheader.h"
#include "ipc/bridge.h"
#include "ipc/view.h"

#include <cassert>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace IPC {
	/**
	* @class Client
	* @brief An interface to the 64-bit server for the 32-bit client.
	* 
	* Client provides an interface to RPC to the server process. The current main purpose of the server is to host the
	* distant land QuadTrees and search them for visible meshes, providing the visible set to the client. To support
	* this, the server provides an API to allocate shared vectors in which the visible sets (or other data) can be
	* stored and shared with the client.
	* 
	* Because rendering is done on the client side, D3D resources must be allocated on the client side. However, the
	* server's distant land structures contain references to these resources. The server therefore provides APIs for
	* the client to push resource information to the server during distant land initialization. The remainder of the
	* API deals with controlling settings related to visible distant meshes and searching the QuadTrees for currently
	* visible meshes.
	* 
	* The server process must be started by the client via the startServer method. This method blocks until the server
	* signals that it has finished initializing and is ready to accept RPCs.
	* 
	* To provide opportunities for parallelism, all RPC methods are asynchronous except the ones that contain the word
	* "blocking". For asynchronous calls that return a value, there will be a corresponding `await` method that will
	* block until the result is available and return it. For asynchronous calls that don't return a value, you can use
	* the generic `waitForCompletion` method to wait for the RPC to complete. The blocking methods will return the
	* result directly.
	* 
	* Only one RPC may be active at a time. If an attempt is made to start another RPC while a previous one is still
	* active, the new RPC will block until the previous RPC is complete. This means that it's not necessary to
	* explicitly wait for RPC completion if you don't care about the results. You can fire off an asynchronous call and
	* move on, and the next RPC request will block if necessary before starting.
	*/
	class Client {
		HANDLE m_sharedMem;
		HANDLE m_rpcStartEvent;
		union {
			struct {
				HANDLE m_process;
				HANDLE m_rpcCompleteEvent;
			};
			HANDLE m_waitHandles[2];
		};
		Parameters* m_ipcParameters;
		bool m_isRpcPending;

		bool beginRpc(Command command);
		WakeReason tryWaitForCompletion(DWORD ms = MaxWait);

	public:
		Client();
		~Client();
		Client(const Client&) = delete;
		Client& operator=(const Client&) = delete;

		bool startServer(const char* executable);
		bool isServerActive();

		/**
		* @brief Asynchronously allocate a shared vector.
		* @param elementSize The size in bytes of the type of element that will be stored in the vector.
		* @param windowSizeInElements The number of elements that will be visible in a single window of the client view.
		*                             The size of the window will be rounded up to a multiple of the system allocation granularity.
		* @param maxSizeInElements The maximum number of elements to reserve memory for in the vector. The size of the
		*                          reservation will be rounded up to a multiple of the system allocation granularity.
		* @param initialCapacity Number of elements to initially commit memory for.
		* @return Whether the RPC was issued successfully.
		*/
		bool allocVec(std::size_t elementSize, std::size_t windowSizeInElements, std::size_t maxSizeInElements, std::size_t initialCapacity);

		/**
		* @brief Await the result of a previous asynchronous vector allocation.
		* @return A VecView with a view into the vector on success, or std::nullopt on failure.
		*/
		template<typename T>
		std::optional<VecView<T>> awaitAllocVec() {
			assert(m_ipcParameters->command == Command::AllocVec);

			auto result = waitForCompletion();
			if (result != WakeReason::Complete) {
				LOG::logline("Vec allocation RPC failed");
				return std::nullopt;
			}

			auto& params = m_ipcParameters->params.allocVecParams;
			if (params.id == InvalidVector) {
				LOG::logline("Vec allocation rejected by server");
				return std::nullopt;
			}

			assert(sizeof(T) == params.elementSize);

			// recalculate elements per window
			auto windowElements = params.windowBytes / sizeof(T);
			VecView<T> view(params.id, static_cast<VecBase::VecShare*>(params.header32), static_cast<std::size_t>(windowElements), static_cast<std::size_t>(params.windowBytes),
				static_cast<std::size_t>((params.reservedBytes / params.windowBytes) * windowElements), static_cast<std::size_t>(params.reservedBytes), static_cast<std::size_t>(params.headerBytes));
			if (!view.init()) {
				return std::nullopt;
			}

			return view;
		}

		/**
		* @brief Synchronously allocate a shared vector.
		* @param windowSizeInElements The number of elements that will be visible in a single window of the client view.
		*                             The size of the window will be rounded up to a multiple of the system allocation granularity.
		* @param maxSizeInElements The maximum number of elements to reserve memory for in the vector. The size of the
		*                          reservation will be rounded up to a multiple of the system allocation granularity.
		* @param initialCapacity Number of elements to initially commit memory for.
		* @return A VecView with a view into the vector on success, or std::nullopt on failure.
		*/
		template<typename T>
		std::optional<VecView<T>> allocVecBlocking(std::size_t windowSizeInElements, std::size_t maxSizeInElements, std::size_t initialCapacity) {
			if (!allocVec(sizeof(T), windowSizeInElements, maxSizeInElements, initialCapacity)) {
				return std::nullopt;
			}

			return awaitAllocVec<T>();
		}

		/**
		* @brief Asynchronously deallocate a shared vector.
		* 
		* Make sure any VecViews of the vector are destroyed prior to this call, otherwise the deallocation will fail.
		* 
		* @param id The ID of the vector to deallocate.
		* @return Whether the RPC was issued successfully.
		*/
		bool freeVec(VecId id);

		/**
		* @brief Await the result of a previous vector deallocation request.
		* @return Whether the vector was actually freed.
		*/
		bool awaitFreeVec();

		/**
		* @brief Synchronously deallocate a shared vector.
		*
		* Make sure any VecViews of the vector are destroyed prior to this call, otherwise the deallocation will fail.
		*
		* @param id The ID of the vector to deallocate.
		* @return Whether the vector was actually freed.
		*/
		bool freeVecBlocking(VecId id);

		/**
		* @brief Asynchronously update mesh dynamic visibility flags.
		* @param flags ID of a shared vector which the client has filled with flags to be updated.
		* @return Whether the RPC was issued successfully.
		*/
		bool updateDynVis(VecId flags);

		/**
		* @brief Inform the server of distant static D3D resources.
		* @param distantStatics ID of a shared vector of DistantStatic objects.
		* @param distantSubsets ID of a shared vector of DistantSubset objects.
		* @return Whether the RPC was issued successfully.
		*/
		bool initDistantStatics(VecId distantStatics, VecId distantSubsets);

		/**
		* @brief Inform the server of distant landscape D3D resources.
		* @param landscapeBuffers ID of a shared vector of LandscapeBuffers objects.
		* @return Whether the RPC was issued successfully.
		*/
		bool initLandscape(VecId landscapeBuffers);

		/**
		* @brief Update the current worldspace by informing the server of the player's current cell.
		* @param cellname The name of the player's current cell.
		* @return Whether the RPC was successful.
		*/
		bool setWorldSpaceBlocking(const std::string& cellname);

		/**
		* @brief Asynchronously do a coarse search for visible meshes.
		* @param visibleSet ID of a shared vector of RenderMesh objects which will be populated with the results of the search.
		* @param viewFrustum The camera's current view frustum.
		* @param setFlags Flags indicating which types of meshes to search for. One or more of VIS_NEAR, VIS_FAR, VIS_VERY_FAR,
		*                 VIS_STATIC (= all 3 of the preceding flags), VIS_GRASS, or VIS_LAND.
		* @param sort The desired sorting of the result set, if any. If no sorting is requested (the default), the server will
		*             enable parallel writing on the vector, allowing the client to iterate over the results as they're
		*             populated, if desired (@ref VecView::start_read).
		* @return Whether the RPC was issued successfully.
		*/
		bool getVisibleMeshesCoarse(VecId visibleSet, const ViewFrustum& viewFrustum, DWORD setFlags, VisibleSetSort sort = VisibleSetSort::None);

		/**
		* @brief Asynchronously search for visible meshes.
		* @param visibleSet ID of a shared vector of RenderMesh objects which will be populated with the results of the search.
		* @param viewFrustum The camera's current view frustum.
		* @param viewSphere A sphere defining the region within the draw distance.
		* @param setFlags Flags indicating which types of meshes to search for. One or more of VIS_NEAR, VIS_FAR, VIS_VERY_FAR,
		*                 VIS_STATIC (= all 3 of the preceding flags), VIS_GRASS, or VIS_LAND.
		* @param sort The desired sorting of the result set, if any. If no sorting is requested (the default), the server will
		*             enable parallel writing on the vector, allowing the client to iterate over the results as they're
		*             populated, if desired (@ref VecView::start_read).
		* @return Whether the RPC was issued successfully.
		*/
		bool getVisibleMeshes(VecId visibleSet, const ViewFrustum& viewFrustum, const D3DXVECTOR4& viewSphere, DWORD setFlags, VisibleSetSort sort = VisibleSetSort::None);

		/**
		* @brief Asynchronously sort an already-populated visible set.
		* @param visibleSet ID of a filled shared vector of RenderMesh objects.
		* @param sort The type of sort desired.
		* @return Whether the RPC was issued successfully.
		*/
		bool sortVisibleSet(VecId visibleSet, VisibleSetSort sort);

		WakeReason waitForCompletion(DWORD ms = MaxWait);
	};
}