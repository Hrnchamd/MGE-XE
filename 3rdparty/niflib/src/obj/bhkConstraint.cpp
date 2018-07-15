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
#include "../../include/obj/bhkConstraint.h"
#include "../../include/obj/bhkEntity.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkConstraint::TYPE("bhkConstraint", &bhkSerializable::TYPE );

bhkConstraint::bhkConstraint() : numEntities((unsigned int)0), priority((unsigned int)1) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkConstraint::~bhkConstraint() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkConstraint::GetType() const {
	return TYPE;
}

NiObject * bhkConstraint::Create() {
	return new bhkConstraint;
}

void bhkConstraint::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkSerializable::Read( in, link_stack, info );
	NifStream( numEntities, in, info );
	entities.resize(numEntities);
	for (unsigned int i1 = 0; i1 < entities.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( priority, in, info );

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkConstraint::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkSerializable::Write( out, link_map, missing_link_stack, info );
	numEntities = (unsigned int)(entities.size());
	NifStream( numEntities, out, info );
	for (unsigned int i1 = 0; i1 < entities.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*entities[i1]), out );
		} else {
			if ( entities[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(entities[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( entities[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( priority, out, info );

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkConstraint::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkSerializable::asString();
	numEntities = (unsigned int)(entities.size());
	out << "  Num Entities:  " << numEntities << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < entities.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Entities[" << i1 << "]:  " << entities[i1] << endl;
		array_output_count++;
	};
	out << "  Priority:  " << priority << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkConstraint::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkSerializable::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < entities.size(); i1++) {
		entities[i1] = FixLink<bhkEntity>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkConstraint::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkSerializable::GetRefs();
	for (unsigned int i1 = 0; i1 < entities.size(); i1++) {
	};
	return refs;
}

std::list<NiObject *> bhkConstraint::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkSerializable::GetPtrs();
	for (unsigned int i1 = 0; i1 < entities.size(); i1++) {
		if ( entities[i1] != NULL )
			ptrs.push_back((NiObject *)(entities[i1]));
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

void bhkConstraint::AddEntity( bhkEntity * obj ) {
   entities.push_back( obj );
}

void bhkConstraint::RemoveEntity( bhkEntity * obj ) {
   //Search Effect list for the one to remove
   for ( vector< bhkEntity * >::iterator it = entities.begin(); it != entities.end(); ) {
      if ( *it == obj ) {
         it = entities.erase( it );
      } else {
         ++it;
      }
   }
}

void bhkConstraint::ClearEntities() {
   entities.clear();
}

vector< bhkEntity * > bhkConstraint::GetEntities() const {
   return entities;
}

//--END CUSTOM CODE--//
