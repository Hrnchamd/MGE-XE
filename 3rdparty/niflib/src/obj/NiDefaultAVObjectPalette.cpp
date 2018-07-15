/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiDefaultAVObjectPalette.h"
#include "../../include/gen/AVObject.h"
#include "../../include/obj/NiAVObject.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiDefaultAVObjectPalette::TYPE("NiDefaultAVObjectPalette", &NiAVObjectPalette::TYPE );

NiDefaultAVObjectPalette::NiDefaultAVObjectPalette() : unknownInt((unsigned int)0), numObjs((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiDefaultAVObjectPalette::~NiDefaultAVObjectPalette() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiDefaultAVObjectPalette::GetType() const {
	return TYPE;
}

NiObject * NiDefaultAVObjectPalette::Create() {
	return new NiDefaultAVObjectPalette;
}

void NiDefaultAVObjectPalette::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiAVObjectPalette::Read( in, link_stack, info );
	NifStream( unknownInt, in, info );
	NifStream( numObjs, in, info );
	objs.resize(numObjs);
	for (unsigned int i1 = 0; i1 < objs.size(); i1++) {
		NifStream( objs[i1].name, in, info );
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiDefaultAVObjectPalette::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiAVObjectPalette::Write( out, link_map, missing_link_stack, info );
	numObjs = (unsigned int)(objs.size());
	NifStream( unknownInt, out, info );
	NifStream( numObjs, out, info );
	for (unsigned int i1 = 0; i1 < objs.size(); i1++) {
		NifStream( objs[i1].name, out, info );
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*objs[i1].avObject), out );
		} else {
			if ( objs[i1].avObject != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(objs[i1].avObject) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( objs[i1].avObject );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiDefaultAVObjectPalette::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiAVObjectPalette::asString();
	numObjs = (unsigned int)(objs.size());
	out << "  Unknown Int:  " << unknownInt << endl;
	out << "  Num Objs:  " << numObjs << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < objs.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Name:  " << objs[i1].name << endl;
		out << "    AV Object:  " << objs[i1].avObject << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiDefaultAVObjectPalette::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiAVObjectPalette::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < objs.size(); i1++) {
		objs[i1].avObject = FixLink<NiAVObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiDefaultAVObjectPalette::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiAVObjectPalette::GetRefs();
	for (unsigned int i1 = 0; i1 < objs.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> NiDefaultAVObjectPalette::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiAVObjectPalette::GetPtrs();
	for (unsigned int i1 = 0; i1 < objs.size(); i1++) {
		if ( objs[i1].avObject != NULL )
			ptrs.push_back((NiObject *)(objs[i1].avObject));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

vector<Ref<NiAVObject> > NiDefaultAVObjectPalette::GetObjs() const {
   vector<NiAVObjectRef> objRefs;
   for (vector<AVObject>::const_iterator itr = objs.begin(); itr != objs.end(); ++itr) {
      objRefs.push_back(itr->avObject);
   }
	return objRefs;
}

void NiDefaultAVObjectPalette::SetObjs( const vector<Ref<NiAVObject> >& value ) {
   objs.clear();
   for (vector<NiAVObjectRef>::const_iterator itr = value.begin(); itr != value.end(); ++itr) {
      AVObject obj;
      obj.name = (*itr)->GetName();
      obj.avObject = (*itr);
      objs.push_back(obj);
   }
}

bool NiDefaultAVObjectPalette::AddObj( Ref<NiAVObject > obj ) {
  for (vector<AVObject>::iterator itr = objs.begin(); itr != objs.end(); ++itr) {
    if ( (*itr).avObject == obj ) {
      return false;
    }
  }

  struct AVObject avo;
  avo.name = obj->GetName();
  avo.avObject = obj;

  objs.push_back(avo);
  numObjs++;

  return false;
}

bool NiDefaultAVObjectPalette::RemoveObj( Ref<NiAVObject > obj ) {
  for (vector<AVObject>::iterator itr = objs.begin(); itr != objs.end(); ++itr) {
    if ( (*itr).avObject == obj ) {
      objs.erase(itr);
      numObjs--;

      return true;
    }
  }

  return false;
}

void NiDefaultAVObjectPalette::ReplaceObj( const Ref<NiAVObject> newobj, const Ref<NiAVObject> oldobj ) {
  for (vector<AVObject>::iterator itr = objs.begin(); itr != objs.end(); ++itr) {
    if ( (*itr).avObject == oldobj ) {
      (*itr).name = newobj->GetName();
      (*itr).avObject = newobj;
    }
  }
}

//--END CUSTOM CODE--//
