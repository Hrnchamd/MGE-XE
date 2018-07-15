/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/nifxml_niflib.py Python script.

#include "obj/NiObject.h"
#include "Ref.h"
#include <stdexcept>
namespace Niflib {

using namespace std;

const char FIX_LINK_POP_ERROR[] = "Trying to pop a link from empty stack. This is probably a bug.";
const char FIX_LINK_INDEX_ERROR[] = "Object index was not found in object map.  This NIF file may be invalid or imporperly supported.";
const char FIX_LINK_CAST_ERROR[] = "Link could not be cast to required type during file read. This NIF file may be invalid or improperly supported.";

template <class T>
Ref<T> FixLink( const map<unsigned,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	if (link_stack.empty()) {
		throw runtime_error(FIX_LINK_POP_ERROR);
	}
	unsigned int index = link_stack.front();
	link_stack.pop_front();
	NiObjectRef missing_obj;
	if (!missing_link_stack.empty()) {
		missing_obj = missing_link_stack.front();
		missing_link_stack.pop_front();
	}

	//Check if link is NULL
	if ( info.version > VER_3_3_0_13) {
	    if ( index == 0xFFFFFFFF) {
			return DynamicCast<T>(missing_obj);
	    }
	} else {
	    if ( index == 0 ) {
			return DynamicCast<T>(missing_obj);
	    }
	}

	map<unsigned int,NiObjectRef>::const_iterator it = objects.find(index);
	if ( it == objects.end() ) {
		if ( info.version > VER_3_3_0_13 ) {
			throw runtime_error(FIX_LINK_INDEX_ERROR);
		} else {
			return NULL;
		}
	}
		
	Ref<T> object = DynamicCast<T>(it->second);
	if ( object == NULL ) {
		stringstream ss;
		ss << FIX_LINK_CAST_ERROR << endl;
		ss << "Type of object with index " << index << " was:  " << it->second->GetType().GetTypeName() << endl;
		ss << "Required type was:  " << T::TYPE.GetTypeName() << endl;
		throw runtime_error( ss.str().c_str() );
	}

	return object;
}

} //End namespace Niflib

