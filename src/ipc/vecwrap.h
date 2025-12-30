#pragma once

#include "ipc/vec.h"
#include "ipc/view.h"
#include "mge/quadtree.h"

#include <utility>
#include <vector>

// wrapper types to provide a consistent interface to different types of containers for VisibleSet

class StlVector {
	std::vector<const RenderMesh*> m_vector;
	std::vector<const RenderMesh*>::iterator m_it;
	std::vector<const RenderMesh*>::iterator m_end;

public:
	StlVector();
	StlVector(std::vector<const RenderMesh*>&& vector);
	StlVector& operator=(const StlVector& other);

	void restart();

	const RenderMesh& first();
	const RenderMesh& next();

	void start_write();

	void start_read();

	bool push_back(const RenderMesh& value);

	bool end_write();

	void end_read();

	bool at_end();

	std::uint32_t size() const;

	bool reserve(std::uint32_t count);

	void clear();

	void truncate(std::uint32_t count);

	void sort_by_state();

	void sort_by_texture();

	std::vector<const RenderMesh*>::iterator begin();
	std::vector<const RenderMesh*>::iterator end();
};

class IpcClientVector {
	IPC::VecView<RenderMesh> m_view;
	bool m_isAtBeginning;

public:
	IpcClientVector();
	IpcClientVector(const IPC::VecView<RenderMesh>& view);
	IpcClientVector(IPC::VecView<RenderMesh>&& view);
	IpcClientVector& operator=(const IpcClientVector& other);

	void restart();

	const RenderMesh& first();
	const RenderMesh& next();

	void start_write();

	void start_read();

	bool push_back(const RenderMesh& value);

	bool end_write();

	void end_read();

	bool at_end();

	std::uint32_t size() const;

	bool reserve(std::uint32_t count);

	void clear();

	void truncate(std::uint32_t count);

	IPC::VecView<RenderMesh> begin();
	IPC::VecView<RenderMesh> end();
};

class IpcServerVector {
	IPC::Vec<RenderMesh>& m_vec;
	IPC::Vec<RenderMesh>::iterator m_it;

public:
	IpcServerVector(IPC::Vec<RenderMesh>& view);
	IpcServerVector& operator=(const IpcServerVector& other);

	void restart();

	const RenderMesh& first();
	const RenderMesh& next();

	void start_write();

	void start_read();

	bool push_back(const RenderMesh& value);

	bool end_write();

	void end_read();

	bool at_end();

	std::uint32_t size() const;

	bool reserve(std::uint32_t count);

	void clear();

	void truncate(std::uint32_t count);

	void sort_by_state();

	void sort_by_texture();

	IPC::Vec<RenderMesh>::iterator begin();
	IPC::Vec<RenderMesh>::iterator end();
};