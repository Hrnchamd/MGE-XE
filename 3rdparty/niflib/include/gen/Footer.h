/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _FOOTER_H_
#define _FOOTER_H_

#include "../NIF_IO.h"
#include "../obj/NiObject.h"

// Include structures
#include "../Ref.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;

/*! The NIF file footer. */
struct Footer {
	/*! Default Constructor */
	NIFLIB_API Footer();
	/*! Default Destructor */
	NIFLIB_API ~Footer();
	/*! Copy Constructor */
	NIFLIB_API Footer( const Footer & src );
	/*! Copy Operator */
	NIFLIB_API Footer & operator=( const Footer & src );
	/*! The number of root references. */
	mutable unsigned int numRoots;
	/*!
	 * List of root NIF objects. If there is a camera, for 1st person view, then this
	 * NIF object is referred to as well in this list, even if it is not a root object
	 * (usually we want the camera to be attached to the Bip Head node).
	 */
	vector<Ref<NiObject > > roots;
	NIFLIB_HIDDEN void Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info );
	NIFLIB_HIDDEN void Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const;
	NIFLIB_HIDDEN string asString( bool verbose = false ) const;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
