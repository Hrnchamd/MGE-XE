/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/ObjectRegistry.h"

namespace Niflib {

map<string, obj_factory_func> ObjectRegistry::object_map;

void ObjectRegistry::RegisterObject( const string & type_name, obj_factory_func create_func ) {
	object_map[type_name] = create_func;
}

NiObject * ObjectRegistry::CreateObject( const string & type_name ) {
	map<string, obj_factory_func>::iterator it;
	it = object_map.find(type_name);

	if ( it != object_map.end() ) {
		//Requested type has been registered
		return it->second();
	} else {
		//An unknown type has been encountered
		return NULL; //Return null
	}
}

} //End namespace Niflib
