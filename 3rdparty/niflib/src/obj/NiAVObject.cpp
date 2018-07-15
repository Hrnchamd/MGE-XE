/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/obj/NiNode.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiAVObject.h"
#include "../../include/gen/BoundingBox.h"
#include "../../include/obj/NiCollisionObject.h"
#include "../../include/obj/NiProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiAVObject::TYPE("NiAVObject", &NiObjectNET::TYPE );

NiAVObject::NiAVObject() : flags((unsigned short)0), unknownShort1((unsigned short)8), scale(1.0f), numProperties((unsigned int)0), unknown2((byte)0), hasBoundingBox(false), collisionObject(NULL) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	parent = NULL;


	parent = NULL;

	//--END CUSTOM CODE--//
}

NiAVObject::~NiAVObject() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//Clear Properties
	ClearProperties();

	//Clear Collision Object Link
	if ( collisionObject != NULL ) {
		collisionObject->SetTarget(NULL);
	}

	//--END CUSTOM CODE--//
}

const Type & NiAVObject::GetType() const {
	return TYPE;
}

NiObject * NiAVObject::Create() {
	return new NiAVObject;
}

void NiAVObject::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObjectNET::Read( in, link_stack, info );
	if ( info.version >= 0x03000000 ) {
		NifStream( flags, in, info );
	};
	if ( ( info.version >= 0x14020007 ) && ( ((info.userVersion >= 11) && (info.userVersion2 > 26)) ) ) {
		NifStream( unknownShort1, in, info );
	};
	NifStream( translation, in, info );
	NifStream( rotation, in, info );
	NifStream( scale, in, info );
	if ( info.version <= 0x04020200 ) {
		NifStream( velocity, in, info );
	};
	if ( ((info.version < 0x14020007) || (info.userVersion <= 11)) ) {
		NifStream( numProperties, in, info );
		properties.resize(numProperties);
		for (unsigned int i2 = 0; i2 < properties.size(); i2++) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
	};
	if ( info.version <= 0x02030000 ) {
		for (unsigned int i2 = 0; i2 < 4; i2++) {
			NifStream( unknown1[i2], in, info );
		};
		NifStream( unknown2, in, info );
	};
	if ( ( info.version >= 0x03000000 ) && ( info.version <= 0x04020200 ) ) {
		NifStream( hasBoundingBox, in, info );
		if ( hasBoundingBox ) {
			NifStream( boundingBox.unknownInt, in, info );
			NifStream( boundingBox.translation, in, info );
			NifStream( boundingBox.rotation, in, info );
			NifStream( boundingBox.radius, in, info );
		};
	};
	if ( info.version >= 0x0A000100 ) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAVObject::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObjectNET::Write( out, link_map, missing_link_stack, info );
	numProperties = (unsigned int)(properties.size());
	if ( info.version >= 0x03000000 ) {
		NifStream( flags, out, info );
	};
	if ( ( info.version >= 0x14020007 ) && ( ((info.userVersion >= 11) && (info.userVersion2 > 26)) ) ) {
		NifStream( unknownShort1, out, info );
	};
	NifStream( translation, out, info );
	NifStream( rotation, out, info );
	NifStream( scale, out, info );
	if ( info.version <= 0x04020200 ) {
		NifStream( velocity, out, info );
	};
	if ( ((info.version < 0x14020007) || (info.userVersion <= 11)) ) {
		NifStream( numProperties, out, info );
		for (unsigned int i2 = 0; i2 < properties.size(); i2++) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*properties[i2]), out );
			} else {
				if ( properties[i2] != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(properties[i2]) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( properties[i2] );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
	};
	if ( info.version <= 0x02030000 ) {
		for (unsigned int i2 = 0; i2 < 4; i2++) {
			NifStream( unknown1[i2], out, info );
		};
		NifStream( unknown2, out, info );
	};
	if ( ( info.version >= 0x03000000 ) && ( info.version <= 0x04020200 ) ) {
		NifStream( hasBoundingBox, out, info );
		if ( hasBoundingBox ) {
			NifStream( boundingBox.unknownInt, out, info );
			NifStream( boundingBox.translation, out, info );
			NifStream( boundingBox.rotation, out, info );
			NifStream( boundingBox.radius, out, info );
		};
	};
	if ( info.version >= 0x0A000100 ) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*collisionObject), out );
		} else {
			if ( collisionObject != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(collisionObject) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( collisionObject );
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

std::string NiAVObject::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObjectNET::asString();
	numProperties = (unsigned int)(properties.size());
	out << "  Flags:  " << flags << endl;
	out << "  Unknown Short 1:  " << unknownShort1 << endl;
	out << "  Translation:  " << translation << endl;
	out << "  Rotation:  " << rotation << endl;
	out << "  Scale:  " << scale << endl;
	out << "  Velocity:  " << velocity << endl;
	out << "  Num Properties:  " << numProperties << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < properties.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Properties[" << i1 << "]:  " << properties[i1] << endl;
		array_output_count++;
	};
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 1[" << i1 << "]:  " << unknown1[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Has Bounding Box:  " << hasBoundingBox << endl;
	if ( hasBoundingBox ) {
		out << "    Unknown Int:  " << boundingBox.unknownInt << endl;
		out << "    Translation:  " << boundingBox.translation << endl;
		out << "    Rotation:  " << boundingBox.rotation << endl;
		out << "    Radius:  " << boundingBox.radius << endl;
	};
	out << "  Collision Object:  " << collisionObject << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiAVObject::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObjectNET::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( ((info.version < 0x14020007) || (info.userVersion <= 11)) ) {
		for (unsigned int i2 = 0; i2 < properties.size(); i2++) {
			properties[i2] = FixLink<NiProperty>( objects, link_stack, missing_link_stack, info );
		};
	};
	if ( info.version >= 0x0A000100 ) {
		collisionObject = FixLink<NiCollisionObject>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiAVObject::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObjectNET::GetRefs();
	for (unsigned int i1 = 0; i1 < properties.size(); i1++) {
		if ( properties[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(properties[i1]));
	};
	if ( collisionObject != NULL )
		refs.push_back(StaticCast<NiObject>(collisionObject));
	return refs;
}

std::list<NiObject *> NiAVObject::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObjectNET::GetPtrs();
	for (unsigned int i1 = 0; i1 < properties.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

Matrix44 NiAVObject::GetLocalTransform() const {
	return Matrix44( translation, rotation, scale );
}

Matrix44 NiAVObject::GetWorldTransform() const {
	//Get Parent Transform if there is one
	NiNodeRef par = GetParent();

	if ( par != NULL ) {
		//Multipy local matrix and parent world matrix for result
		return GetLocalTransform() * par->GetWorldTransform();
	}
	else {
		//No parent transform, simply return local transform
		return GetLocalTransform();
	}
}

void NiAVObject::SetParent( NiNode * new_parent ) {
	parent = new_parent;
}

Ref<NiNode> NiAVObject::GetParent() const {
	return parent;
}

void NiAVObject::AddProperty( NiProperty * obj ) {
	properties.push_back( obj );
}

void NiAVObject::RemoveProperty( NiProperty * obj ) {
	//Search property list for the one to remove
	for ( vector< NiPropertyRef >::iterator it = properties.begin(); it != properties.end(); ) {
		if ( *it == obj ) {
			it = properties.erase( it );
		} else {
			++it;
		}
	}
}

void NiAVObject::ClearProperties() {
	properties.clear();
}

vector< Ref<NiProperty> > NiAVObject::GetProperties() const {
	return properties;
}

Ref<NiProperty> NiAVObject::GetPropertyByType( const Type & compare_to ) {
	for ( unsigned int i = 0; i < properties.size(); ++i ) {
		if ( properties[i] == NULL ) {
			continue;
		}
		if ( properties[i]->IsSameType( compare_to ) ) {
			return properties[i];
		}
	}
	//No matching properties found, return NULL
	return NULL;
}

unsigned short NiAVObject::GetFlags() const {
	return flags;
}

void NiAVObject::SetFlags( unsigned short n ) {
	flags = n;
}

Matrix33 NiAVObject::GetLocalRotation() const {
	return rotation;
}

void NiAVObject::SetLocalRotation( const Matrix33 & n ) {
	rotation = n;
}

Vector3 NiAVObject::GetLocalTranslation() const {
	return translation;
}

void NiAVObject::SetLocalTranslation( const Vector3 & n ) {
	translation = n;
}

float NiAVObject::GetLocalScale() const {
	return scale;
}

void NiAVObject::SetLocalScale( float n ) {
	scale = n;
}

Vector3 NiAVObject::GetVelocity() const {
	return velocity;
}

void NiAVObject::SetVelocity( const Vector3 & n ) {
	velocity = n;
}

NiAVObject::CollisionType NiAVObject::GetCollisionMode() const {
	//Mask off the 2 significant bits
	unsigned short temp = flags & 0x6;

	//Shift the result one right
	return NiAVObject::CollisionType(temp >> 1);
}

void NiAVObject::SetCollisionMode( CollisionType value ) {
	unsigned short temp = (unsigned short)value;

	//Shift one left
	temp = temp << 1;

	//Zero out the values in the flags for the 2 significant bits
	flags = flags & 0xFFF9;

	//Now combine values
	flags = flags | temp;
}

Ref<NiCollisionObject > NiAVObject::GetCollisionObject() const {
  return collisionObject;
}

void NiAVObject::SetCollisionObject( NiCollisionObject * value ) {
	if ( value != NULL ) {
		if ( value->GetTarget() != NULL ) {
			throw runtime_error( "You have attempted to add a collision object to a NiAVObject which is already attached to another NiAVObject." );
		}
		value->SetTarget( this );
	}

	if ( collisionObject !=NULL ) {
		//Remove unlink previous collision object from this node
		collisionObject->SetTarget(NULL);
	}

	collisionObject = value;
}

void NiAVObject::SetLocalTransform( const Matrix44 & n ) {
	n.Decompose( translation, rotation, scale );
}

bool NiAVObject::GetVisibility() const {
	return !( flags & 1 );
}

void NiAVObject::SetVisibility( bool n ) {
	//Only do anything if the value is different from what it already is
	if ( GetVisibility() != n ) {
		//Flip the bit
		flags ^= 1;
	}
}

bool NiAVObject::HasBoundingBox() const {
	return hasBoundingBox;
}

void NiAVObject::ClearBoundingBox() {
	hasBoundingBox = false;
}

BoundingBox NiAVObject::GetBoundingBox() const {
	if ( hasBoundingBox == true ) {
		return boundingBox;
	} else {
		throw runtime_error("This NIAVObject has no Bounding Box.");
	}
}

void NiAVObject::SetBoundingBox( const BoundingBox & n ) {
	boundingBox = n;
	hasBoundingBox = true;
}

//--END CUSTOM CODE--//
