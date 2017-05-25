/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//#define DEBUG // this will produce lots of output
//#define PRINT_OBJECT_NAMES
//#define PRINT_OBJECT_CONTENTS
//#define DEBUG_LINK_PHASE
//#define DEBUG_HEADER_FOOTER

#include "../include/niflib.h"
#include "../include/NIF_IO.h"
#include "../include/ObjectRegistry.h"
#include "../include/kfm.h"
#include "../include/obj/NiObject.h"
#include "../include/obj/NiNode.h"
#include "../include/obj/NiAVObject.h"
#include "../include/obj/NiTextKeyExtraData.h"
#include "../include/obj/NiSequenceStreamHelper.h"
#include "../include/obj/NiControllerManager.h"
#include "../include/obj/NiControllerSequence.h"
#include "../include/obj/NiStringPalette.h"
#include "../include/obj/NiSkinPartition.h"
#include "../include/obj/NiTimeController.h"
#include "../include/obj/NiSingleInterpController.h"
#include "../include/obj/NiInterpolator.h"
#include "../include/obj/NiKeyframeController.h"
#include "../include/obj/NiKeyframeData.h"
#include "../include/obj/NiTransformInterpolator.h"
#include "../include/obj/NiTransformController.h"
#include "../include/obj/NiTransformData.h"
#include "../include/obj/NiStringExtraData.h"
#include "../include/obj/NiExtraData.h"
#include "../include/obj/bhkRigidBody.h"
#include "../include/obj/bhkCollisionObject.h"
#include "../include/gen/Header.h"
#include "../include/gen/Footer.h"

namespace Niflib {

//Object Registration
bool g_objects_registered = false;
void RegisterObjects();

//Utility Functions
void EnumerateObjects( NiObject * root, map<Type*,unsigned int> & type_map, map<NiObjectRef, unsigned int> & link_map, bool reverse = false );
NiObjectRef FindRoot( vector<NiObjectRef> const & objects );
NiObjectRef GetObjectByType( NiObject * root, const Type & type );

/*!
 * Helper function to split off animation from a nif tree. If no animation groups are defined, then both xnif_root and xkf_root will be NULL.
 * \param root_object The root object of the full tree.
 * \param xnif_root The root object of the tree without animation.
 * \param xkf_roots The root objects of the animation trees.
 * \param kfm The KFM structure (if required by style).
 * \param kf_type What type of keyframe tree to write (Morrowind style, DAoC style, ...).
 * \param info A NifInfo structure that contains information such as the version of the NIF file to create.
 */
static void SplitNifTree( NiObject * root_object, NiObject * xnif_root, list<NiObjectRef> & xkf_roots, Kfm & kfm, int kf_type, const NifInfo & info );

//--Function Bodies--//

NiObjectRef ReadNifTree( string const & file_name, NifInfo * info ) {
	//Read object list
	vector<NiObjectRef> objects = ReadNifList( file_name, info );
	return FindRoot( objects );
}

NiObjectRef ReadNifTree( istream & in, NifInfo * info ) {
	//Read object list
	vector<NiObjectRef> objects = ReadNifList( in, info );
	return FindRoot( objects );
}

NiObjectRef FindRoot( vector<NiObjectRef> const & objects ) {
	//--Look for a NiNode that has no parents--//

	//Find the first NiObjectNET derived object
	NiAVObjectRef root;
	for (unsigned int i = 0; i < objects.size(); ++i) {
		root = DynamicCast<NiAVObject>(objects[i]);
		if ( root != NULL ) {
			break;
		}
	}

	//Make sure a node was found, if not return first node
	if ( root == NULL )
		return objects[0];

	//Move up the chain to the root node
	while ( root->GetParent() != NULL ) {
		root = StaticCast<NiAVObject>(root->GetParent());
	}

	return StaticCast<NiObject>(root);
}

unsigned int GetNifVersion( string const & file_name ) {
	//--Open File--//
	ifstream in( file_name.c_str(), ifstream::binary );

	//Check if file exists
	if ( in.is_open() == false ) {
		//File does not exist, throw exception
		stringstream ss;
		ss << "A file with the name " << file_name << " does not exist.";
		throw runtime_error( ss.str() );
	}

	//--Read Header String--//

	HeaderString header;
	NifInfo info;
	NifStream( header, in, info );

	return info.version;
}

vector<NiObjectRef> ReadNifList( string const & file_name, NifInfo * info ) {

	//--Open File--//
	ifstream in( file_name.c_str(), ifstream::binary );

	//Check if file exists
	if ( in.is_open() == false ) {
		//File does not exist, throw exception
		stringstream ss;
		ss << "A file with the name " << file_name << " does not exist.";
		throw runtime_error( ss.str() );
	}

	vector<NiObjectRef> ret = ReadNifList( in, info );
	in.close();
	return ret;
}

vector<NiObjectRef> ReadNifList( istream & in, NifInfo * info ) {

	//Ensure that objects are registered
	if ( g_objects_registered == false ) {
		g_objects_registered = true;
		RegisterObjects();
	}

	//--Read Header--//
	Header header;

	//Create a new NifInfo if one isn't given.
	bool delete_info = false;
	if ( info == NULL ) {
		info = new NifInfo();
		delete_info = true;
	}

	//Read header.
	*info = header.Read( in );

	//If NifInfo structure is provided, fill it with info from header
	info->version = header.version;
	info->userVersion = header.userVersion;
	info->userVersion2 = header.userVersion2;
	info->endian = EndianType(header.endianType);
	info->creator = header.creator.str;
	info->exportInfo1 = header.exportInfo1.str;
	info->exportInfo2 = header.exportInfo2.str;

#ifdef DEBUG_HEADER_FOOTER
	//Print debug output for header
	cout << header.asString();
#endif

#ifdef PRINT_OBJECT_NAMES
	cout << endl << "Reading Objects:";
#endif

	//--Read Objects--//
	size_t numObjects = header.numBlocks;
	map<unsigned,NiObjectRef> objects; //Map to hold objects by number
	vector<NiObjectRef> obj_list; //Vector to hold links in the order they were created.
	list<unsigned int> link_stack; //List to add link values to as they're read in from the file
	string objectType;
	stringstream errStream;

	//Loop through all objects in the file
	unsigned int i = 0;
	NiObjectRef new_obj;
	while (true) {
		//Check for EOF
		if (in.eof() ) {
			errStream << "End of file reached prematurely.  This NIF may be corrupt or improperly supported." << endl;
			if ( new_obj != NULL ) {
				errStream << "Last successfuly read object was:  " << endl;
				errStream << "====[ " << "Object " << i - 1 << " | " << new_obj->GetType().GetTypeName() << " ]====" << endl;
				errStream << new_obj->asString();
			} else {
				errStream << "No objects were read successfully." << endl;
			}
			throw runtime_error( errStream.str() );
		}
	
		//There are two main ways to read objects
		//One before version 5.0.0.1 and one after
		if ( header.version >= 0x05000001 ) {
			//From version 5.0.0.1 to version 10.0.1.106  there is a zero byte at the begining of each object
			
			if ( header.version <= VER_10_1_0_106 ) {
				unsigned int checkValue = ReadUInt( in );
				if ( checkValue != 0 ) {
					//Throw an exception if it's not zero
					errStream << "Read failue - Bad object position.  Invalid check value:  " << checkValue << endl;
					if ( new_obj != NULL ) {
						errStream << "Last successfuly read object was:  " << endl;
						errStream << "====[ " << "Object " << i - 1 << " | " << new_obj->GetType().GetTypeName() << " ]====" << endl;
						errStream << new_obj->asString();
					} else {
						errStream << "No objects were read successfully." << endl;
					}
					throw runtime_error( errStream.str() );
				}
			}

			// Find which NIF object type this is by using the header arrays
			objectType = header.blockTypes[ header.blockTypeIndex[i] ];

#ifdef PRINT_OBJECT_NAMES
			cout << endl << i << ":  " << objectType;
#endif
		} else {
			// Find which object type this is by reading the string at this location
			unsigned int objectTypeLength = ReadUInt( in );
			if (objectTypeLength > 30 || objectTypeLength < 6) {
				errStream << "Read failue - Bad object position.  Invalid Type Name Length:  " << objectTypeLength  << endl;
				if ( new_obj != NULL ) {
					errStream << "Last successfuly read object was:  " << endl;
					errStream << "====[ " << "Object " << i - 1 << " | " << new_obj->GetType().GetTypeName() << " ]====" << endl;
					errStream << new_obj->asString();
				} else {
					errStream << "No objects were read successfully." << endl;
				}
				throw runtime_error( errStream.str() );
			}
			char* charobjectType = new char[objectTypeLength + 1];
			in.read( charobjectType, objectTypeLength );
			charobjectType[objectTypeLength] = 0;
			objectType = string(charobjectType);
			delete [] charobjectType;

#ifdef PRINT_OBJECT_NAMES
			cout << endl << i << ":  " << objectType;
#endif

			if ( header.version < VER_3_3_0_13 ) {
				//There can be special commands instead of object names
				//in these versions

				if ( objectType == "Top Level Object" ) {
					//Just continue on to the next object
					continue;
				}

				if ( objectType == "End Of File" ) {
					//File is finished
					break;
				}
			}

			if ( (objectType[0] != 'N' || objectType[1] != 'i') && (objectType[0] != 'R' || objectType[1] != 'o') && (objectType[0] != 'A' || objectType[1] != 'v')) {
				errStream << "Read failue - Bad object position.  Invalid Type Name:  " << objectType << endl;
				if ( new_obj != NULL ) {
					errStream << "Last successfuly read object was:  " << endl;
					errStream << "====[ " << "Object " << i - 1 << " | " << new_obj->GetType().GetTypeName() << " ]====" << endl;
					errStream << new_obj->asString();
				} else {
					errStream << "No objects were read successfully." << endl;
				}
				throw runtime_error( errStream.str() );
			}
		}

		//Create object of the type that was found
		new_obj = ObjectRegistry::CreateObject(objectType);

		//Check for an unknown object type
		if ( new_obj == NULL ) {
			errStream << "Unknown object type encountered during file read:  " << objectType << endl;
			if ( new_obj != NULL ) {
				errStream << "Last successfuly read object was:  " << endl;
				errStream << "====[ " << "Object " << i - 1 << " | " << new_obj->GetType().GetTypeName() << " ]====" << endl;
				errStream << new_obj->asString();
			} else {
				errStream << "No objects were read successfully." << endl;
			}
			throw runtime_error( errStream.str() );
		}

		unsigned int index;
		if ( header.version < VER_3_3_0_13 ) {
			//These old versions have a pointer value after the name
			//which is used as the index
			index = ReadUInt(in);
		} else {
			//These newer verisons use their position in the file as their index
			index = i;
		}

		//Read new object
		new_obj->Read( in, link_stack, *info );

		//Add object to map
		objects[index] = new_obj;

		//Add object to list
		obj_list.push_back(new_obj);
			
#ifdef PRINT_OBJECT_CONTENTS
		cout << endl << new_obj->asString() << endl;
#endif

		if ( header.version >= VER_3_3_0_13 ) {
			//We know the number of objects, so increment the count
			//and break if we've finished
			++i;
			if ( i >= numObjects ) {
				break;
			}
		}
	}

	//--Read Footer--//
	Footer footer;
	footer.Read( in, link_stack, *info );

#ifdef DEBUG_HEADER_FOOTER
	//Print footer debug output
	footer.asString();
#endif
	
	//This should fail, and trigger the in.eof() flag
	ReadByte( in ); 
	if ( ! in.eof() ) {
		throw runtime_error("End of file not reached.  This NIF may be corrupt or improperly supported.");
	}

#ifdef DEBUG_LINK_PHASE
	cout << "Link Stack:" << endl;
	list<unsigned int>::iterator it;
	for ( it = link_stack.begin(); it != link_stack.end(); ++it ) {
		cout << *it << endl;
	}

	cout << "Fixing Links:"  << endl;
#endif
	//--Now that all objects are read, go back and fix the links--//
	

	for ( unsigned int i = 0; i < obj_list.size(); ++i ) {
#ifdef DEBUG_LINK_PHASE
		cout << "   " << i << ":  " << obj_list[i] << endl;
#endif
		//Fix links & other pre-processing
		obj_list[i]->FixLinks( objects, link_stack, *info );
	}

	//delete info if it was dynamically allocated
	if ( delete_info ) {
		delete info;
	}

	//Return completed object list
	return obj_list;
}

// Writes a valid Nif File given an ostream, a list to the root objects of a file tree
void WriteNifTree( ostream & out, list<NiObjectRef> const & roots, const NifInfo & info ) {
	//Enumerate all objects in tree
	map<Type*,unsigned int> type_map;
	map<NiObjectRef, unsigned int> link_map;

	for (list<NiObjectRef>::const_iterator it = roots.begin(); it != roots.end(); ++it) {
		EnumerateObjects( (*it), type_map, link_map );
	}

	//Build vectors for reverse look-up
	vector<NiObjectRef> objects(link_map.size());
	for ( map<NiObjectRef, unsigned int>::iterator it = link_map.begin(); it != link_map.end(); ++it ) {
		objects[it->second] = it->first;
	}

	vector<const Type*> types(type_map.size());
	for ( map<Type*, unsigned int>::iterator it = type_map.begin(); it != type_map.end(); ++it ) {
		types[it->second] = it->first;
	}

	unsigned version = info.version;
	unsigned user_version = info.userVersion;

	//--Write Header--//
	Header header;
	header.version = info.version;
	header.userVersion = info.userVersion;
	header.userVersion2 = info.userVersion2;
	header.endianType = info.endian;
	header.creator.str = info.creator;
	header.exportInfo1.str = info.exportInfo1;
	header.exportInfo2.str = info.exportInfo2;
	header.copyright[0].line = "Numerical Design Limited, Chapel Hill, NC 27514";
	header.copyright[1].line = "Copyright (c) 1996-2000";
	header.copyright[2].line = "All Rights Reserved";
	
	//Set Type Names
	header.blockTypes.resize( types.size() );
	for ( unsigned int i = 0; i < types.size(); ++i ) {
		header.blockTypes[i] = types[i]->GetTypeName();

	}

	//Set type number of each object
	header.blockTypeIndex.resize( objects.size() );
	for ( unsigned int i = 0; i < objects.size(); ++i ) {
		header.blockTypeIndex[i] = type_map[(Type*)&(objects[i]->GetType())];
	}

	//Write header to file
	header.Write( out, info );

#ifdef PRINT_OBJECT_NAMES
	cout << endl << "Writing Objects:";
#endif

	//--Write Objects--//
	for (unsigned int i = 0; i < objects.size(); ++i) {

#ifdef PRINT_OBJECT_NAMES
		cout << endl << i << ":  " << objects[i]->GetType().GetTypeName();
#endif

		if ( version < VER_3_3_0_13 ) {
			//Check if this object is one of the roots.
			for ( list<NiObjectRef>::const_iterator it = roots.begin(); it != roots.end(); ++it ) {
				if ( objects[i] == *it ) {
					//Write "Top Level Object"
					WriteString( "Top Level Object", out );
					break;
				}
			}

			//Write Object Type
			WriteString( objects[i]->GetType().GetTypeName() , out );
			//Write pointer number of object
			WriteUInt( (unsigned int)&(*objects[i]), out );

			
		} else if (version < 0x05000001) {
			//Write Object Type
			WriteString( objects[i]->GetType().GetTypeName() , out );
		} else if (version >= 0x05000001 && version <= VER_10_1_0_0 ) {
			WriteUInt( 0, out );
		}

		objects[i]->Write( out, link_map, info );
	}

	//--Write Footer--//

	if ( version < VER_3_3_0_13 ) {
		//Write "End Of File"
		WriteString( "End Of File", out );
	} else {
		Footer footer;
		footer.numRoots = 0;
		if (roots.size() == 1) {
			const NiObjectRef& root = roots.front();
			if (root->IsDerivedType(NiControllerSequence::TYPE)) {
				// KF animation files allow for multiple roots of type NiControllerSequence
				for ( unsigned int i = 0; i < objects.size(); ++i ) {
					if (objects[i]->IsDerivedType(NiControllerSequence::TYPE)) {
						footer.roots.push_back(objects[i]);
					}
				}
			} else { // just assume its correctly passed in 
				footer.numRoots = 1;
				footer.roots.resize(1);
				footer.roots[0] = root;
			}
		} else {
			footer.numRoots = (unsigned int)roots.size();
			footer.roots.insert(footer.roots.end(), roots.begin(), roots.end());
		}
		footer.Write( out, link_map, info );
	}
}

// Writes a valid Nif File given a file name, a pointer to the root object of a file tree
void WriteNifTree( string const & file_name, NiObject * root, const NifInfo & info ) {
   //Open output file
   ofstream out( file_name.c_str(), ofstream::binary );

   	//Check if file exists
	if ( out.is_open() == false ) {
		//File does not exist, throw exception
		stringstream ss;
		ss << "Could not create file " << file_name << ".  Does the path exist?";
		throw runtime_error( ss.str() );
	}

   list<NiObjectRef> roots;
   roots.push_back(root);
   WriteNifTree( out, roots, info );

   //Close file
   out.close();
}

void WriteNifTree( string const & file_name, list<NiObjectRef> const & roots, const NifInfo & info ) {
   //Open output file
   ofstream out( file_name.c_str(), ofstream::binary );

   WriteNifTree( out, roots, info );

   //Close file
   out.close();
}

// Writes a valid Nif File given an ostream, a pointer to the root object of a file tree
void WriteNifTree( ostream & out, NiObject * root, const NifInfo & info ) {
   list<NiObjectRef> roots;
   roots.push_back(root);
   WriteNifTree( out, roots, info );
}

void EnumerateObjects( NiObject * root, map<Type*,unsigned int> & type_map, map<NiObjectRef, unsigned int> & link_map, bool reverse ) {
	//Ensure that this object has not already been visited
	if ( link_map.find( root ) != link_map.end() ) {
		//This object has already been visited.  Return.
		return;
	}

	//Add this object type to the map if it isn't there already
	if ( type_map.find( (Type*)&(root->GetType()) ) == type_map.end() ) {
		//The type has not yet been registered, so register it
		size_t n = type_map.size();
		type_map[ (Type*)&(root->GetType()) ] = (unsigned int)n;
	}

   // Oblivion has very rigid requirements about object ordering and the bhkRigidBody 
   //   must be after its children. Hopefully this can be removed and replaced with 
   //   a more generic mechanism in the future.
	Type *t = (Type*)&(root->GetType());
   if (  reverse
      || t->IsDerivedType(bhkRigidBody::TYPE) 
      || t->IsDerivedType(bhkCollisionObject::TYPE)
      )
   {
      reverse = true;
   }

   // If reverse is set then add the link after children otherwise add it before
   if (!reverse) {
      size_t n = link_map.size();
      link_map[root] = (unsigned int)n;
   }

   //Call this function on all links of this object	
   list<NiObjectRef> links = root->GetRefs();
   for ( list<NiObjectRef>::iterator it = links.begin(); it != links.end(); ++it ) {
      if ( *it != NULL ) {
         EnumerateObjects( *it, type_map, link_map, reverse );
      }
   }

   if (reverse) {
      size_t n = link_map.size();
      link_map[root] = (unsigned int)n;
   }
}

//TODO: Should this be returning an object of a derived type too?
// Searches for the first object in the hierarchy of type.
NiObjectRef GetObjectByType( NiObject * root, const Type & type ) {
	if ( root->IsSameType( type ) ) {
		return root;
	}

	list<NiObjectRef> links = root->GetRefs();
	for (list <NiObjectRef>::iterator it = links.begin(); it != links.end(); ++it) {
		// Can no longer guarantee that some objects won't be visited twice.  Oh well.
		NiObjectRef result = GetObjectByType( *it, type );
		if ( result != NULL ) {
			return result;
		}
	};

	return NULL; // return null reference
};

//TODO: Should this be returning all objects of a derived type too?
// Returns all in the in the tree of type.
list<NiObjectRef> GetAllObjectsByType( NiObject * root, const Type & type ) {
	list<NiObjectRef> result;

	Type t = root->GetType();
	if ( root->IsSameType(type) ) {
		result.push_back( root );
	}
	list<NiObjectRef> links = root->GetRefs();
	for (list<NiObjectRef>::iterator it = links.begin(); it != links.end(); ++it ) {
		// Can no longer guarantee that some objects won't be visited twice.  Oh well.
		if ( *it != NULL ) {
			list<NiObjectRef> childresult = GetAllObjectsByType( *it, type );
			result.merge( childresult );
		}
	};
	return result;
};

// Create a valid file name
static std::string CreateFileName(std::string name) {
   std::string retname = name;
   std::string::size_type off = 0;
   std::string::size_type pos = 0;
   for (;;) {
      pos = retname.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_^$~!#%&-{}()@'` ", off);
      if (pos == std::string::npos)
         break;
      retname[pos] = '_';
      off = pos;
   }
   return retname;   
}

//TODO:  This was written by Amorilia.  Figure out how to fix it.
static void SplitNifTree( NiObject * root_object, NiObjectRef & xnif_root, list<NiObjectRef> & xkf_roots, Kfm & kfm, int kf_type, const NifInfo & info ) {
	// Do we have animation groups (a NiTextKeyExtraData object)?
	// If so, create XNif and XKf trees.
	NiObjectRef txtkey = GetObjectByType( root_object, NiTextKeyExtraData::TYPE );
	NiTextKeyExtraDataRef txtkey_obj;
	if ( txtkey != NULL ) {
		txtkey_obj = DynamicCast<NiTextKeyExtraData>(txtkey);
	}
	if ( txtkey_obj != NULL ) {
		if ( kf_type == KF_MW ) {
			// Construct the XNif file...

			xnif_root = CloneNifTree( root_object, info.version, info.userVersion );
				
			// Now search and locate newer timeframe controllers and convert to keyframecontrollers
			list<NiObjectRef> mgrs = GetAllObjectsByType( xnif_root, NiControllerManager::TYPE );
			for ( list<NiObjectRef>::iterator it = mgrs.begin(); it != mgrs.end(); ++it) {
				NiControllerManagerRef mgr = DynamicCast<NiControllerManager>(*it);
				if ( mgr == NULL ) {
					continue;
				}
				NiObjectNETRef target = mgr->GetTarget();
				target->RemoveController( StaticCast<NiTimeController>(mgr) );
				vector<NiControllerSequenceRef> seqs = mgr->GetControllerSequences();
				for (vector<NiControllerSequenceRef>::iterator itr = seqs.begin(); itr != seqs.end(); ++itr) {
					NiControllerSequenceRef seq = (*itr);
					MergeNifTrees(DynamicCast<NiNode>(target), seq, info.version, info.userVersion );
				}
			 }

			// Now the XKf file...
			// Create xkf root header.
			NiSequenceStreamHelperRef xkf_stream_helper = new NiSequenceStreamHelper;
			xkf_roots.push_back( StaticCast<NiObject>(xkf_stream_helper) );
					
			// Append NiNodes with a NiKeyFrameController as NiStringExtraData objects.
			list< pair< NiNodeRef, NiKeyframeControllerRef> > node_controllers;

			list<NiObjectRef> nodes = GetAllObjectsByType( xnif_root, NiNode::TYPE );
			for ( list<NiObjectRef>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
				NiNodeRef node = DynamicCast<NiNode>(*it);
				if ( node == NULL ) {
					continue;
				}

				//Find the first NiKeyframeController in the controller list, if any
				list<NiTimeControllerRef> controllers = node->GetControllers();
				NiKeyframeControllerRef key_controller;
				for ( list<NiTimeControllerRef>::iterator it = controllers.begin(); it != controllers.end(); ++it ) {

					if ((*it)->IsDerivedType(NiKeyframeController::TYPE)) {
						key_controller = StaticCast<NiKeyframeController>(*it);
					} else if ((*it)->IsDerivedType(NiTransformController::TYPE)) {
						NiTransformControllerRef trans = StaticCast<NiTransformController>(*it);
						NiTransformInterpolatorRef interp = DynamicCast<NiTransformInterpolator>(trans->GetInterpolator());
						if (interp != NULL) {
							NiTransformDataRef transData = interp->GetData();
							if (transData != NULL) {
								NiKeyframeDataRef data = new NiKeyframeData();
								data->SetRotateType( transData->GetRotateType() );
								data->SetTranslateType( transData->GetTranslateType() );
								data->SetScaleType( transData->GetScaleType() );
								data->SetXRotateType( transData->GetXRotateType() );
								data->SetYRotateType( transData->GetYRotateType() );
								data->SetZRotateType( transData->GetZRotateType() );
								data->SetTranslateKeys( transData->GetTranslateKeys() );
								data->SetQuatRotateKeys( transData->GetQuatRotateKeys() );
								data->SetScaleKeys( transData->GetScaleKeys() );
								data->SetXRotateKeys( transData->GetXRotateKeys() );
								data->SetYRotateKeys( transData->GetYRotateKeys() );
								data->SetZRotateKeys( transData->GetZRotateKeys() );

								key_controller = new NiKeyframeController();
								key_controller->SetFlags( trans->GetFlags() );
								key_controller->SetFrequency( trans->GetFrequency() );
								key_controller->SetPhase( trans->GetPhase() );
								key_controller->SetStartTime( trans->GetStartTime() );
								key_controller->SetStopTime( trans->GetStopTime() );
								key_controller->SetData( data );
								break;
							}
						}
					}
				}

				//If this node has a keyframe controller, put it in the list
				if ( key_controller != NULL ) {
					node_controllers.push_back( pair<NiNodeRef,NiKeyframeControllerRef>( node, key_controller ) );
				}
			}
			
			for ( list< pair< NiNodeRef, NiKeyframeControllerRef> >::reverse_iterator it = node_controllers.rbegin(); it != node_controllers.rend(); ++it ) {
				//Add string data				
				NiStringExtraDataRef nodextra = new NiStringExtraData;
				nodextra->SetData( it->first->GetName() );
				xkf_stream_helper->AddExtraData( StaticCast<NiExtraData>(nodextra), info.version );

				NiKeyframeControllerRef controller = it->second;
				(it->first)->RemoveController( StaticCast<NiTimeController>(controller) );

				xkf_stream_helper->AddController( StaticCast<NiTimeController>(controller) );
			}

			// Add a copy of the NiTextKeyExtraData object to the XKf header.
			NiTextKeyExtraDataRef xkf_txtkey_obj = new NiTextKeyExtraData;
			xkf_stream_helper->AddExtraData( StaticCast<NiExtraData>(xkf_txtkey_obj), info.version );
			xkf_txtkey_obj->SetKeys( txtkey_obj->GetKeys() );

		} else if (kf_type == KF_CIV4) {
			// Construct the Nif file without transform controllers ...
			xnif_root = CloneNifTree( root_object, info.version, info.userVersion );

			list<NiObjectRef> mgrs = GetAllObjectsByType( xnif_root, NiControllerManager::TYPE );
			for ( list<NiObjectRef>::iterator it = mgrs.begin(); it != mgrs.end(); ++it) {
				NiControllerManagerRef mgr = DynamicCast<NiControllerManager>(*it);
				if ( mgr == NULL ) {
				   continue;
				}
				NiObjectNETRef target = mgr->GetTarget();
				target->RemoveController( StaticCast<NiTimeController>(mgr) );
				vector<NiControllerSequenceRef> seqs = mgr->GetControllerSequences();
				for (vector<NiControllerSequenceRef>::iterator itr = seqs.begin(); itr != seqs.end(); ++itr) {
				   xkf_roots.push_back( StaticCast<NiObject>(*itr) );
				}
			}
		} else {
			throw runtime_error("KF splitting for the requested game is not yet implemented.");
		}
	} else {
		// no animation groups: nothing to do
		xnif_root = root_object;
	};
}

//TODO:  This was written by Amorilia.  Figure out how to fix it.
void WriteFileGroup( string const & file_name, NiObject * root_object, const NifInfo & info, ExportOptions export_files, NifGame kf_type ) {
	// Get base filename.
	unsigned int file_name_slash = (unsigned int)(file_name.rfind("\\") + 1);
	string file_name_path = file_name.substr(0, file_name_slash);
	string file_name_base = file_name.substr(file_name_slash, file_name.length());
	unsigned int file_name_dot = (unsigned int)(file_name_base.rfind("."));
	file_name_base = file_name_base.substr(0, file_name_dot);
	
	// Deal with the simple case first
	if ( export_files == EXPORT_NIF )
		WriteNifTree( file_name_path + file_name_base + ".nif", root_object, info ); // simply export the NIF file!
	// Now consider all other cases
	else if ( kf_type == KF_MW ) {
		if ( export_files == EXPORT_NIF_KF ) {
			// for Morrowind we must also write the full NIF file
			WriteNifTree( file_name_path + file_name_base + ".nif", root_object, info ); // simply export the NIF file!
			NiObjectRef xnif_root;
			list<NiObjectRef> xkf_roots;
			Kfm kfm; // dummy
			SplitNifTree( root_object, xnif_root, xkf_roots, kfm, kf_type, info );
			if ( xnif_root != NULL && !xkf_roots.empty()) {
				WriteNifTree( file_name_path + "x" + file_name_base + ".nif", xnif_root, info );
				WriteNifTree( file_name_path + "x" + file_name_base + ".kf", xkf_roots.front(), info );
			};
		} else
			throw runtime_error("Invalid export option.");
   } else if (kf_type == KF_CIV4) {

      NiObjectRef xnif_root;
      list<NiObjectRef> xkf_roots;
      Kfm kfm; // dummy
	  SplitNifTree( root_object, xnif_root, xkf_roots, kfm, kf_type, info );
      if ( export_files == EXPORT_NIF || export_files == EXPORT_NIF_KF || export_files == EXPORT_NIF_KF_MULTI ) {
         WriteNifTree( file_name_path + file_name_base + ".nif", xnif_root, info );
      }
      if ( export_files == EXPORT_NIF_KF || export_files == EXPORT_KF ) {
         WriteNifTree( file_name_path + file_name_base + ".kf", xkf_roots, info );
      } else if ( export_files == EXPORT_NIF_KF_MULTI || export_files == EXPORT_KF_MULTI ) {
         for ( list<NiObjectRef>::iterator it = xkf_roots.begin(); it != xkf_roots.end(); ++it ) {
            NiControllerSequenceRef seq = DynamicCast<NiControllerSequence>(*it);
            if (seq == NULL)
               continue;
            string path = file_name_path + file_name_base + "_" + CreateFileName(seq->GetTargetName()) + "_" + CreateFileName(seq->GetName()) + ".kf";
            WriteNifTree( path, StaticCast<NiObject>(seq), info );
         }         
      }
   } else
		throw runtime_error("Not yet implemented.");
};

void MapNodeNames( map<string,NiNodeRef> & name_map, NiNode * par ) {
	//Add the par node to the map, and then call this function for each of its children
	name_map[par->GetName()] = par;

	
	vector<NiAVObjectRef> links = par->GetChildren();
	for (vector<NiAVObjectRef>::iterator it = links.begin(); it != links.end(); ++it) {
		NiNodeRef child_node = DynamicCast<NiNode>(*it);
		if ( child_node != NULL ) {
			MapNodeNames( name_map, child_node );
		};
	};
}

//This function will merge two scene graphs by attatching new objects to the correct position
//on the existing scene graph.  In other words, it deals only with adding new nodes, not altering
//existing nodes by changing their data or attatched properties
void MergeSceneGraph( map<string,NiNodeRef> & name_map, NiNode * root, NiAVObject * par ) {
	//Check if this object's name exists in the object map
	string name = par->GetName();

	if ( name_map.find(name) != name_map.end() ) {
		//This object already exists in the original file, so continue on to its children, if it is a NiNode
		
		NiNodeRef par_node = DynamicCast<NiNode>(par);
		if ( par_node != NULL ) {
			vector<NiAVObjectRef> children = par_node->GetChildren();
			for ( vector<NiAVObjectRef>::iterator it = children.begin(); it != children.end(); ++it ) {
				if ( (*it) != NULL ) {
					MergeSceneGraph( name_map, root, *it );
				};
			};
		}
		return;
	}

	//This object has a new name and either it has no parent or its parent has a name that is
	// in the list.  Attatch it to the object with the same name as its parent
	//all child objects will follow along.
	NiNodeRef par_par = par->GetParent();

	if ( par_par == NULL) {
		//This object has a new name and no parents.  That means it is the root object.
		//of a disimilar Nif file.
			
		//Check whether we have a NiNode ( a node that might have children) or not.
		NiNodeRef par_node = DynamicCast<NiNode>(par);
		if ( par_node == NULL ) {
			//This is not a NiNode class, so simply add it as a new child of the
			//target root node
			root->AddChild( par );
		} else {
			//This is a NiNode class, so merge its child list with that of the root
			vector<NiAVObjectRef> children = par_node->GetChildren();
			for ( unsigned int i = 0; i < children.size(); ++i ) {
				root->AddChild( children[i] );
			}
		}
	} else {
		//This object has a new name and has a parent with a name that already exists.
		//Attatch it to the object in the target tree that matches the name of its
		//parent

		//TODO:  Implement children
		////Remove this object from its old parent
		//par_par->GetAttr("Children")->RemoveLinks( par );

		//Get the object to attatch to
		NiObjectRef attatch = DynamicCast<NiObject>(name_map[par_par->GetName()]);

		//TODO:  Implement children
		////Add this object as new child
		//attatch->GetAttr("Children")->AddLink( par );
	}
}

void MergeNifTrees( NiNode * target, NiAVObject * right, unsigned version, unsigned user_version ) {
	//For now assume that both are normal Nif trees just to verify that it works

	//Make a clone of the tree to add
	stringstream tmp;
	//WriteNifTree( tmp, right, version );
	tmp.seekg( 0, ios_base::beg );
	NiAVObjectRef new_tree = right;// ReadNifTree( tmp ); TODO: Figure out why this doesn't work

	//Create a list of names in the target
	map<string,NiNodeRef> name_map;
	MapNodeNames( name_map, target );

	////Reassign any cross references in the new tree to point to objects in the
	////target tree with the same names
	//ReassignTreeCrossRefs( name_map, new_tree );

	//Use the name map to merge the Scene Graphs
	MergeSceneGraph( name_map, target, new_tree );
}

//Version for merging KF Trees rooted by a NiControllerSequence
void MergeNifTrees( NiNode * target, NiControllerSequence * right, unsigned version, unsigned user_version ) {
	//Map the node names
	map<string,NiNodeRef> name_map;
	MapNodeNames( name_map, target );

	//TODO:  Allow this to merge a KF sequence into a file that already has
	//sequences in it by appending all the keyframe data to the end of
	//existing controllers

	//Get the NiTextKeyExtraData, clone it, and attach it to the target node
	NiTextKeyExtraDataRef txt_key = right->GetTextKeyExtraData();
	if ( txt_key != NULL ) {
		NiObjectRef tx_clone = txt_key->Clone( version, user_version );
		NiExtraDataRef ext_dat = DynamicCast<NiExtraData>(tx_clone);
		if ( ext_dat != NULL ) {
			target->AddExtraData( ext_dat, version );
		}
	}

	//Atach it to

	//Get the controller data
	vector<ControllerLink> data = right->GetControllerData();

	//Connect a clone of all the interpolators/controllers to the named node
	for ( unsigned int i = 0; i < data.size(); ++i ) {
		//Get strings
		//TODO: Find out if other strings are needed
		string node_name, ctlr_type;
		NiStringPaletteRef str_pal = data[i].stringPalette;
		if ( str_pal == NULL ) {
			node_name = data[i].nodeName;
			ctlr_type = data[i].controllerType;
		} else {
			node_name = str_pal->GetSubStr( data[i].nodeNameOffset );
			ctlr_type = str_pal->GetSubStr( data[i].controllerTypeOffset );
		}
		//Make sure there is a node with this name in the target tree
		if ( name_map.find( node_name ) != name_map.end() ) {
			//See if we're dealing with an interpolator or a controller
			if ( data[i].controller != NULL ) {
				//Clone the controller and attached data and
				//add it to the named node
				NiObjectRef clone = CloneNifTree( StaticCast<NiObject>(data[i].controller), version, user_version );
				NiTimeControllerRef ctlr = DynamicCast<NiTimeController>(clone);
				if ( ctlr != NULL ) {
					name_map[node_name]->AddController( ctlr );
				}
			} else if ( data[i].interpolator != NULL ) {
				//Clone the interpolator and attached data and
				//attach it to the specific type of controller that's
				//connected to the named node
				NiNodeRef node = name_map[node_name];
				list<NiTimeControllerRef> ctlrs = node->GetControllers();
				NiSingleInterpControllerRef ctlr;
				for ( list<NiTimeControllerRef>::iterator it = ctlrs.begin(); it != ctlrs.end(); ++it ) {
					if ( *it != NULL && (*it)->GetType().GetTypeName() == ctlr_type ) {
						ctlr = DynamicCast<NiSingleInterpController>(*it);
						if ( ctlr != NULL ) {
							break;
						}
					}
				}

				//If the controller wasn't found, create one of the right type and attach it
				if ( ctlr == NULL ) {
					NiObjectRef new_ctlr = ObjectRegistry::CreateObject( ctlr_type );
					ctlr = DynamicCast<NiSingleInterpController>( new_ctlr );
					if ( ctlr == NULL ) {
						throw runtime_error ("Non-NiSingleInterpController controller found in KF file.");
					}
					node->AddController( StaticCast<NiTimeController>(ctlr) );
				}

				//Clone the interpolator and attached data and
				//add it to controller of matching type that was
				//found
				NiObjectRef clone = CloneNifTree( StaticCast<NiObject>(data[i].interpolator), version, user_version );
				NiInterpolatorRef interp = DynamicCast<NiInterpolator>(clone);
				if ( interp != NULL ) {
					ctlr->SetInterpolator( interp );

					//Set the start/stop time and frequency of this controller
					ctlr->SetStartTime( right->GetStartTime() );
					ctlr->SetStopTime( right->GetStopTime() );
					ctlr->SetFrequency( right->GetFrequency() );
					ctlr->SetPhase( 0.0f ); //TODO:  Is phase somewhere in NiControllerSequence?

					//Set cycle type as well
					switch ( right->GetCycleType() ) {
						case CYCLE_LOOP:
							ctlr->SetFlags( 8 ); //Active
							break;
						case CYCLE_CLAMP:
							ctlr->SetFlags( 12 ); //Active+Clamp
							break;
						case CYCLE_REVERSE:
							ctlr->SetFlags( 10 ); //Active+Reverse
							break;
					}
				}
			}
		}
	}
}

//Version for merging KF Trees rooted by a NiSequenceStreamHelper
void MergeNifTrees( NiNode * target, NiSequenceStreamHelper * right, unsigned version, unsigned user_version ) {
	//Map the node names
	map<string,NiNodeRef> name_map;
	MapNodeNames( name_map, target );

	//TODO: Implement this

}


bool IsSupportedVersion( unsigned int version ) {
	switch (version) {
		case VER_3_0:
		case VER_3_03:
		case VER_3_1:
		case VER_3_3_0_13:
		case VER_4_0_0_0:
		case VER_4_0_0_2:
		case VER_4_1_0_12:
		case VER_4_2_0_2:
		case VER_4_2_1_0:
		case VER_4_2_2_0:
		case VER_10_0_1_0:
		case VER_10_1_0_0:
		case VER_10_0_1_2:
		case VER_10_1_0_106:
		case VER_10_2_0_0:
		case VER_20_0_0_4:
		case VER_20_0_0_5:
			return true;
   }
   return false;
}

unsigned int ParseVersionString(string version) {
	
	unsigned int outver = 0;

	string::size_type start = 0, len, end;
	for( int offset = 3; offset >= 0 && start < version.length(); --offset ) {
		end = version.find_first_of( ".", start );
		
		if ( end == string::npos ) {
			if ( offset > 0 ) {
				//This version has only one period in it.  Take the rest of the numbers one character at a time.
				len = 1;
			} else {
				//We've already taken two characters one at a time, so take the rest all at once.
				len = end;
			}
		} else {
			len = end-start;
			
		}

		int num = 0;
		stringstream sstr( version.substr(start, len) );
		sstr >> num;
		if ( num > 0xFF ) {
			return VER_INVALID;
		}
		outver |= ( num << (offset * 8) );
		if ( len == string::npos ) {
			break;
		}

		if ( end != string::npos ) {
			//account for length of the period
			start += 1;
		}
		start += len;
	}

	if ( outver == 0 ) {
		return VER_INVALID;
	} else {
		return outver;
	}
}

string FormatVersionString(unsigned version) {
	//Cast the version to an array of 4 bytes
	char * byte_ver = (char*)&version;

	//Put the version parts into an integer array, reversing their order
	int int_ver[4] = { byte_ver[3], byte_ver[2], byte_ver[1], byte_ver[0] };
	
	//Format the version string and return it
	stringstream out;

	if ( version >= VER_3_3_0_13 ) {
		//Version 3.3.0.13+ is in x.x.x.x format.
		out << int_ver[0] << "." << int_ver[1] << "." << int_ver[2] << "." << int_ver[3];
	} else {
		//Versions before 3.3.0.13 are in x.x format.
		out << int_ver[0] << "." << int_ver[1];
		if ( int_ver[2] ) {
			out << int_ver[2];
			if ( int_ver[3] ) {
				out << int_ver[3];
			}
		}
	}

	return out.str();
}


Ref<NiObject> CloneNifTree( NiObject * root, unsigned version, unsigned user_version ) {
	//Create a string stream to temporarily hold the state-save of this tree
	stringstream tmp;

	//Write the existing tree into the stringstream
	WriteNifTree( tmp, root, NifInfo(version, user_version) );

	//Read the data back out of the stringstream, returning the new tree
	return ReadNifTree( tmp );
}

void SendNifTreeToBindPos( NiNode * root ) {
	//If this node is a skeleton root, send its children to the bind
	//position

	if ( root == NULL ) {
		throw runtime_error( "Attempted to call SendNifTreeToBindPos on a null reference." );
	}

	if ( root->IsSkeletonRoot() ) {
		root->GoToSkeletonBindPosition();
	}

	//Call this function on any NiNode children
	vector<NiAVObjectRef> children = root->GetChildren();
	for ( unsigned int i = 0; i < children.size(); ++i ) {
		NiNodeRef child = DynamicCast<NiNode>(children[i]);
		if ( child != NULL ) {
			SendNifTreeToBindPos( child );
		}
	}
}

list< Ref<NiNode> > ListAncestors( NiAVObject * leaf ) {
	if ( leaf == NULL ) {
		throw runtime_error("ListAncestors called with a NULL leaf NiNode Ref");
	}

	list<NiNodeRef> ancestors;

	NiNodeRef current = leaf->GetParent();

	while ( current != NULL ) {
		ancestors.push_front(current);

		current = current->GetParent();
	}

	return ancestors;
}

Ref<NiNode> FindCommonAncestor( const vector< Ref<NiAVObject> > & objects ) {

	//create lists of nodes that have an influence and this TriBasedGeom
	//as decendents
	size_t obj_count = objects.size();
	vector< list<NiNodeRef> > ancestors( obj_count );
	
	//Add Ancestors of each object to its corresponding list
	for ( size_t i = 0; i < obj_count; ++i ) {
		ancestors[i] = ListAncestors( objects[i] );
	}

	if ( ancestors[0].size() == 0 ) {
		//All objects must have a parent for there to be a common ancestor, so return NULL
		return NULL;
	}

	NiNodeRef root = ancestors[0].front();
	//Make sure bone and shapes are part of the same tree
	for ( size_t i = 1; i < obj_count; ++i ) {
		if ( ancestors[i].size() == 0 ) {
			//All objects must have a parent for there to be a common ancestor, so return NULL
			return NULL;
		}
		if ( ancestors[i].front() != root ) {
			//These objects are not part of the same tree, so return NULL
			return NULL;
		}
	}

	//Since the first items have been shown to match, pop all the stacks
	for ( size_t i = 0; i < obj_count; ++i ) {
		ancestors[i].pop_front();
	}

	//Now search for the common ancestor
	while(true) {
		bool all_same = true;
		if ( ancestors[0].size() == 0 ) {
			//This list is over, so the last top is the common ancestor
			//break out of the loop
			break;
		}
		NiNodeRef first_ancestor = ancestors[0].front();
		for ( size_t i = 1; i < obj_count; ++i ) {
			if ( ancestors[i].size() == 0 ) {
				//This list is over, so the last top is the common ancestor
				//break out of the loop
				all_same = false;
				break;
			}
			if ( ancestors[i].front() != first_ancestor ) {
				all_same = false;
			}
		}

		if ( all_same == true ) {
			//They're all the same, so set the top, pop all the stacks
			//and look again

			root = ancestors[0].front();
			for ( size_t i = 0; i < obj_count; ++i ) {
				ancestors[i].pop_front();
			}
		} else {
			//One is different, so the last top is the common ancestor.
			//break out of the loop
			break;
		}
	}

	//Return result
	return root;
}

} // namespace NifLib
