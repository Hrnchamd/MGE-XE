/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _OBJECT_REGISTRY_H_
#define _OBJECT_REGISTRY_H_

#include <map>
#include <string>
#include "obj/NiObject.h"

namespace Niflib {

using namespace std;
typedef NiObject * (*obj_factory_func)();

/*!
 * Stores the mapping between object names and factory function pointers to create them
 */
class ObjectRegistry {
public:
	/*!
	 * Registers a new type of NiObject for use by the Read functions.
	 * \param[in] type_name The textual name of the object that will appear in the NIF file.  For example: "NiNode"
	 * \param[in] create_func The Create function of the NiObject that will be called during file reading to initialize new objects of the types encountered in the file.
	 */
	NIFLIB_API static void RegisterObject( const string & type_name, obj_factory_func create_func );

	/*! 
	 * NIFLIB_HIDDEN function.  For internal use only.
	 * Called during file reads to create objects of a named type.
	 */
	NIFLIB_HIDDEN static NiObject * CreateObject( const string & type_name );

private:
	static map<string, obj_factory_func> object_map;
};

} //End namespace Niflib

#endif
