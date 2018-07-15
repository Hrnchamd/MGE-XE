/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//
#include "../../include/obj/bhkShape.h"
//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/bhkRigidBody.h"
#include "../../include/gen/QuaternionXYZW.h"
#include "../../include/obj/bhkSerializable.h"
using namespace Niflib;

//Definition of TYPE constant
const Type bhkRigidBody::TYPE("bhkRigidBody", &bhkEntity::TYPE );

bhkRigidBody::bhkRigidBody() : unknownInt1((int)0), unknownInt2((int)0x00000001), unknown3Ints(3,(int)0,(int)0,(int)0x80000000), collisionResponse_((hkResponseType)RESPONSE_SIMPLE_CONTACT), unknownByte((byte)0xbe), processContactCallbackDelay_((unsigned short)0xffff), unknown2Shorts(2,(unsigned short)35899,(unsigned short)16336), layerCopy((OblivionLayer)OL_STATIC), colFilterCopy((byte)0), skyrimLayerCopy((SkyrimLayer)SKYL_STATIC), flagsAndPartNumberCopy((byte)0), unknown7Shorts(7,(unsigned short)0,(unsigned short)21280,(unsigned short)2481,(unsigned short)62977,(unsigned short)65535,(unsigned short)44,(unsigned short)0), mass(1.0f), linearDamping(0.1f), angularDamping(0.05f), unknownTimefactorOrGravityfactor1(0.0f), unknownTimefactorOrGravityfactor2(0.0f), friction(0.3f), rollingfrictionmultiplier_(0.0f), restitution(0.3f), maxLinearVelocity(250.0f), maxAngularVelocity(31.4159f), penetrationDepth(0.15f), motionSystem((MotionSystem)MO_SYS_DYNAMIC), deactivatorType((DeactivatorType)DEACTIVATOR_NEVER), solverDeactivation((SolverDeactivation)SOLVER_DEACTIVATION_OFF), qualityType((MotionQuality)MO_QUAL_FIXED), unknownInt6((unsigned int)512), unknownInt7((unsigned int)160), unknownInt8((unsigned int)161), unknownInt81((unsigned int)0), numConstraints((unsigned int)0), unknownInt9((unsigned int)0), unknownInt91((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

bhkRigidBody::~bhkRigidBody() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & bhkRigidBody::GetType() const {
	return TYPE;
}

NiObject * bhkRigidBody::Create() {
	return new bhkRigidBody;
}

void bhkRigidBody::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	bhkEntity::Read( in, link_stack, info );
	NifStream( unknownInt1, in, info );
	NifStream( unknownInt2, in, info );
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		NifStream( unknown3Ints[i1], in, info );
	};
	NifStream( collisionResponse_, in, info );
	NifStream( unknownByte, in, info );
	NifStream( processContactCallbackDelay_, in, info );
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		NifStream( unknown2Shorts[i1], in, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimLayerCopy, in, info );
		NifStream( flagsAndPartNumberCopy, in, info );
	} else {
	NifStream( layerCopy, in, info );
	NifStream( colFilterCopy, in, info );
	}
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		NifStream( unknown7Shorts[i1], in, info );
	};
	NifStream( translation, in, info );
	NifStream( rotation.x, in, info );
	NifStream( rotation.y, in, info );
	NifStream( rotation.z, in, info );
	NifStream( rotation.w, in, info );
	NifStream( linearVelocity, in, info );
	NifStream( angularVelocity, in, info );
	NifStream( inertia, in, info );
	NifStream( center, in, info );
	NifStream( mass, in, info );
	NifStream( linearDamping, in, info );
	NifStream( angularDamping, in, info );
	if ( (info.userVersion >= 12) ) {
		NifStream( unknownTimefactorOrGravityfactor1, in, info );
		NifStream( unknownTimefactorOrGravityfactor2, in, info );
	};
	NifStream( friction, in, info );
	if ( (info.userVersion >= 12) ) {
		NifStream( rollingfrictionmultiplier_, in, info );
	};
	NifStream( restitution, in, info );
	NifStream( maxLinearVelocity, in, info );
	NifStream( maxAngularVelocity, in, info );
	NifStream( penetrationDepth, in, info );
	NifStream( motionSystem, in, info );
	NifStream( deactivatorType, in, info );
	NifStream( solverDeactivation, in, info );
	NifStream( qualityType, in, info );
	NifStream( unknownInt6, in, info );
	NifStream( unknownInt7, in, info );
	NifStream( unknownInt8, in, info );
	if ( (info.userVersion >= 12) ) {
		NifStream( unknownInt81, in, info );
	};
	NifStream( numConstraints, in, info );
	constraints.resize(numConstraints);
	for (unsigned int i1 = 0; i1 < constraints.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( (info.userVersion <= 11) ) {
		NifStream( unknownInt9, in, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( unknownInt91, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkRigidBody::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkEntity::Write( out, link_map, missing_link_stack, info );
	numConstraints = (unsigned int)(constraints.size());
	NifStream( unknownInt1, out, info );
	NifStream( unknownInt2, out, info );
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		NifStream( unknown3Ints[i1], out, info );
	};
	NifStream( collisionResponse_, out, info );
	NifStream( unknownByte, out, info );
	NifStream( processContactCallbackDelay_, out, info );
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		NifStream( unknown2Shorts[i1], out, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( skyrimLayerCopy, out, info );
		NifStream( flagsAndPartNumberCopy, out, info );
	} else {
	NifStream( layerCopy, out, info );
	NifStream( colFilterCopy, out, info );
	}
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		NifStream( unknown7Shorts[i1], out, info );
	};
	NifStream( translation, out, info );
	NifStream( rotation.x, out, info );
	NifStream( rotation.y, out, info );
	NifStream( rotation.z, out, info );
	NifStream( rotation.w, out, info );
	NifStream( linearVelocity, out, info );
	NifStream( angularVelocity, out, info );
	NifStream( inertia, out, info );
	NifStream( center, out, info );
	NifStream( mass, out, info );
	NifStream( linearDamping, out, info );
	NifStream( angularDamping, out, info );
	if ( (info.userVersion >= 12) ) {
		NifStream( unknownTimefactorOrGravityfactor1, out, info );
		NifStream( unknownTimefactorOrGravityfactor2, out, info );
	};
	NifStream( friction, out, info );
	if ( (info.userVersion >= 12) ) {
		NifStream( rollingfrictionmultiplier_, out, info );
	};
	NifStream( restitution, out, info );
	NifStream( maxLinearVelocity, out, info );
	NifStream( maxAngularVelocity, out, info );
	NifStream( penetrationDepth, out, info );
	NifStream( motionSystem, out, info );
	NifStream( deactivatorType, out, info );
	NifStream( solverDeactivation, out, info );
	NifStream( qualityType, out, info );
	NifStream( unknownInt6, out, info );
	NifStream( unknownInt7, out, info );
	NifStream( unknownInt8, out, info );
	if ( (info.userVersion >= 12) ) {
		NifStream( unknownInt81, out, info );
	};
	NifStream( numConstraints, out, info );
	for (unsigned int i1 = 0; i1 < constraints.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*constraints[i1]), out );
		} else {
			if ( constraints[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(constraints[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( constraints[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( (info.userVersion <= 11) ) {
		NifStream( unknownInt9, out, info );
	};
	if ( (info.userVersion >= 12) ) {
		NifStream( unknownInt91, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string bhkRigidBody::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << bhkEntity::asString();
	numConstraints = (unsigned int)(constraints.size());
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	out << "  Unknown Int 2:  " << unknownInt2 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 3; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 3 Ints[" << i1 << "]:  " << unknown3Ints[i1] << endl;
		array_output_count++;
	};
	out << "  Collision Response?:  " << collisionResponse_ << endl;
	out << "  Unknown Byte:  " << unknownByte << endl;
	out << "  Process Contact Callback Delay?:  " << processContactCallbackDelay_ << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 2 Shorts[" << i1 << "]:  " << unknown2Shorts[i1] << endl;
		array_output_count++;
	};
	out << "  Layer Copy:  " << layerCopy << endl;
	out << "  Col Filter Copy:  " << colFilterCopy << endl;
	out << "  Skyrim Layer Copy:  " << skyrimLayerCopy << endl;
	out << "  Flags And PartNumber Copy:  " << flagsAndPartNumberCopy << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 7; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 7 Shorts[" << i1 << "]:  " << unknown7Shorts[i1] << endl;
		array_output_count++;
	};
	out << "  Translation:  " << translation << endl;
	out << "  x:  " << rotation.x << endl;
	out << "  y:  " << rotation.y << endl;
	out << "  z:  " << rotation.z << endl;
	out << "  w:  " << rotation.w << endl;
	out << "  Linear Velocity:  " << linearVelocity << endl;
	out << "  Angular Velocity:  " << angularVelocity << endl;
	out << "  Inertia:  " << inertia << endl;
	out << "  Center:  " << center << endl;
	out << "  Mass:  " << mass << endl;
	out << "  Linear Damping:  " << linearDamping << endl;
	out << "  Angular Damping:  " << angularDamping << endl;
	out << "  Unknown TimeFactor or GravityFactor 1:  " << unknownTimefactorOrGravityfactor1 << endl;
	out << "  Unknown TimeFactor or GravityFactor 2:  " << unknownTimefactorOrGravityfactor2 << endl;
	out << "  Friction:  " << friction << endl;
	out << "  RollingFrictionMultiplier?:  " << rollingfrictionmultiplier_ << endl;
	out << "  Restitution:  " << restitution << endl;
	out << "  Max Linear Velocity:  " << maxLinearVelocity << endl;
	out << "  Max Angular Velocity:  " << maxAngularVelocity << endl;
	out << "  Penetration Depth:  " << penetrationDepth << endl;
	out << "  Motion System:  " << motionSystem << endl;
	out << "  Deactivator Type:  " << deactivatorType << endl;
	out << "  Solver Deactivation:  " << solverDeactivation << endl;
	out << "  Quality Type:  " << qualityType << endl;
	out << "  Unknown Int 6:  " << unknownInt6 << endl;
	out << "  Unknown Int 7:  " << unknownInt7 << endl;
	out << "  Unknown Int 8:  " << unknownInt8 << endl;
	out << "  Unknown Int 81:  " << unknownInt81 << endl;
	out << "  Num Constraints:  " << numConstraints << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < constraints.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Constraints[" << i1 << "]:  " << constraints[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown Int 9:  " << unknownInt9 << endl;
	out << "  Unknown Int 91:  " << unknownInt91 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void bhkRigidBody::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	bhkEntity::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < constraints.size(); i1++) {
		constraints[i1] = FixLink<bhkSerializable>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> bhkRigidBody::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = bhkEntity::GetRefs();
	for (unsigned int i1 = 0; i1 < constraints.size(); i1++) {
		if ( constraints[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(constraints[i1]));
	};
	return refs;
}

std::list<NiObject *> bhkRigidBody::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = bhkEntity::GetPtrs();
	for (unsigned int i1 = 0; i1 < constraints.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

OblivionLayer bhkRigidBody::GetLayerCopy() const {
	return layerCopy;
}

void bhkRigidBody::SetLayerCopy( OblivionLayer value ) {
	layerCopy = value;
}

SkyrimLayer bhkRigidBody::GetSkyrimLayerCopy() const {
	return skyrimLayerCopy;
}

void bhkRigidBody::SetSkyrimLayerCopy( SkyrimLayer value ) {
	skyrimLayerCopy = value;
}

Vector4 bhkRigidBody::GetTranslation() const {
	return translation;
}

void bhkRigidBody::SetTranslation( const Vector4 & value ) {
	translation = value;
}

QuaternionXYZW bhkRigidBody::GetRotation() const {
	return rotation;
}

void bhkRigidBody::SetRotation( const QuaternionXYZW & value ) {
	rotation = value;
}

Vector4 bhkRigidBody::GetLinearVelocity() const {
	return linearVelocity;
}

void bhkRigidBody::SetLinearVelocity( const Vector4 & value ) {
	linearVelocity = value;
}

Vector4 bhkRigidBody::GetAngularVelocity() const {
	return angularVelocity;
}

void bhkRigidBody::SetAngularVelocity( const Vector4 & value ) {
	angularVelocity = value;
}

InertiaMatrix  bhkRigidBody::GetInertia() const {
	return inertia;
}

void bhkRigidBody::SetInertia( const InertiaMatrix&  value ) {
	inertia = value;
}

Vector4 bhkRigidBody::GetCenter() const {
	return center;
}

void bhkRigidBody::SetCenter( const Vector4 & value ) {
	center = value;
}

float bhkRigidBody::GetMass() const {
	return mass;
}

void bhkRigidBody::SetMass( float value ) {
	mass = value;
}

float bhkRigidBody::GetLinearDamping() const {
	return linearDamping;
}

void bhkRigidBody::SetLinearDamping( float value ) {
	linearDamping = value;
}

float bhkRigidBody::GetAngularDamping() const {
	return angularDamping;
}

void bhkRigidBody::SetAngularDamping( float value ) {
	angularDamping = value;
}

float bhkRigidBody::GetFriction() const {
	return friction;
}

void bhkRigidBody::SetFriction( float value ) {
	friction = value;
}

float bhkRigidBody::GetRestitution() const {
	return restitution;
}

void bhkRigidBody::SetRestitution( float value ) {
	restitution = value;
}

float bhkRigidBody::GetMaxLinearVelocity() const {
	return maxLinearVelocity;
}

void bhkRigidBody::SetMaxLinearVelocity( float value ) {
	maxLinearVelocity = value;
}

float bhkRigidBody::GetMaxAngularVelocity() const {
	return maxAngularVelocity;
}

void bhkRigidBody::SetMaxAngularVelocity( float value ) {
	maxAngularVelocity = value;
}

float bhkRigidBody::GetPenetrationDepth() const {
	return penetrationDepth;
}

void bhkRigidBody::SetPenetrationDepth( float value ) {
	penetrationDepth = value;
}

MotionSystem bhkRigidBody::GetMotionSystem() const {
	return motionSystem;
}

void bhkRigidBody::SetMotionSystem( MotionSystem value ) {
	motionSystem = value;
}

MotionQuality bhkRigidBody::GetQualityType() const {
	return qualityType;
}

void bhkRigidBody::SetQualityType( MotionQuality value ) {
	qualityType = value;
}

DeactivatorType bhkRigidBody::GetDeactivatorType() const {
	return deactivatorType;
}

void bhkRigidBody::SetDeactivatorType( const DeactivatorType & value ) {
	deactivatorType = value;
}

SolverDeactivation bhkRigidBody::GetSolverDeactivation() const {
	return solverDeactivation;
}

void bhkRigidBody::SetSolverDeactivation( const SolverDeactivation & value ) {
	solverDeactivation = value;
}

void bhkRigidBody::AddConstraint( bhkSerializable * obj ) {
   constraints.push_back( obj );
}

void bhkRigidBody::RemoveConstraint( bhkSerializable * obj ) {
   //Search Effect list for the one to remove
   for ( vector< bhkSerializableRef >::iterator it = constraints.begin(); it != constraints.end(); ) {
      if ( *it == obj ) {
         it = constraints.erase( it );
      } else {
         ++it;
      }
   }
}

void bhkRigidBody::ClearConstraints() {
   constraints.clear();
}

vector< Ref<bhkSerializable> > bhkRigidBody::GetConstraints() const {
   return constraints;
}


// Apply scale factor <scale> on data.
void bhkRigidBody::ApplyScale(float scale)
{
    // apply scale on transform
    translation *= scale;

    // apply scale on center of gravity
    center *= scale;

    // apply scale on inertia tensor
    inertia *= pow(scale, 2.0f);

    //# apply scale on all blocks down the hierarchy
    //ApplyScale(scale)
}

void bhkRigidBody::UpdateMassProperties(float density, bool solid, float mass)
{
    // Look at all the objects under this rigid body and update the mass
    //  center of gravity, and inertia tensor accordingly. If the C{mass} parameter
    //  is given then the C{density} argument is ignored.

	if (mass != 0.0f)
        density = 1.0f;

	if (shape != NULL)
	{
		float volume;
		Vector3 com;
		shape->CalcMassProperties(density, solid, this->mass, volume, com, inertia);
		center = com;
		if (mass != 0.0f)
		{
			float mass_correction = (this->mass != 0.0f) ? mass / this->mass : 1.0f;
			this->mass = mass;
			inertia *= mass_correction;
		}
	}
}

array<7,unsigned short> bhkRigidBody::GetUnknown7Shorts() const {
	return unknown7Shorts;
}

void bhkRigidBody::SetUnknown7Shorts(const array<7,unsigned short> & in ) {
	unknown7Shorts = in;
}

//--END CUSTOM CODE--//
