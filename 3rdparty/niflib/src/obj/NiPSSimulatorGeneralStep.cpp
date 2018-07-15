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
#include "../../include/obj/NiPSSimulatorGeneralStep.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiPSSimulatorGeneralStep::TYPE("NiPSSimulatorGeneralStep", &NiPSSimulatorStep::TYPE );

NiPSSimulatorGeneralStep::NiPSSimulatorGeneralStep() : numSizeKeys((byte)0), sizeLoopBehavior((PSLoopBehavior)0), unknown1(0.0f), unknown2(0.0f), unknown3(0.0f), numColorKeys((byte)0), colorLoopBehavior((PSLoopBehavior)0), numRotationKeys((byte)0), rotationLoopBehavior((PSLoopBehavior)0), growTime(0.0f), shrinkTime(0.0f), growGeneration((unsigned short)0), shrinkGeneration((unsigned short)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiPSSimulatorGeneralStep::~NiPSSimulatorGeneralStep() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiPSSimulatorGeneralStep::GetType() const {
	return TYPE;
}

NiObject * NiPSSimulatorGeneralStep::Create() {
	return new NiPSSimulatorGeneralStep;
}

void NiPSSimulatorGeneralStep::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSimulatorStep::Read( in, link_stack, info );
	NifStream( numSizeKeys, in, info );
	sizeKeys.resize(numSizeKeys);
	for (unsigned int i1 = 0; i1 < sizeKeys.size(); i1++) {
		NifStream( sizeKeys[i1], in, info, 1 );
	};
	if ( info.version >= 0x1E000002 ) {
		NifStream( sizeLoopBehavior, in, info );
	};
	if ( info.version <= 0x14060000 ) {
		NifStream( unknown1, in, info );
		NifStream( unknown2, in, info );
		NifStream( unknown3, in, info );
	};
	if ( info.version >= 0x1E000002 ) {
		NifStream( numColorKeys, in, info );
		colorKeys.resize(numColorKeys);
		for (unsigned int i2 = 0; i2 < colorKeys.size(); i2++) {
			NifStream( colorKeys[i2], in, info, 1 );
		};
		NifStream( colorLoopBehavior, in, info );
		NifStream( numRotationKeys, in, info );
		rotationKeys.resize(numRotationKeys);
		for (unsigned int i2 = 0; i2 < rotationKeys.size(); i2++) {
			NifStream( rotationKeys[i2], in, info, 1 );
		};
		NifStream( rotationLoopBehavior, in, info );
		NifStream( growTime, in, info );
		NifStream( shrinkTime, in, info );
		NifStream( growGeneration, in, info );
		NifStream( shrinkGeneration, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSimulatorGeneralStep::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSimulatorStep::Write( out, link_map, missing_link_stack, info );
	numRotationKeys = (byte)(rotationKeys.size());
	numColorKeys = (byte)(colorKeys.size());
	numSizeKeys = (byte)(sizeKeys.size());
	NifStream( numSizeKeys, out, info );
	for (unsigned int i1 = 0; i1 < sizeKeys.size(); i1++) {
		NifStream( sizeKeys[i1], out, info, 1 );
	};
	if ( info.version >= 0x1E000002 ) {
		NifStream( sizeLoopBehavior, out, info );
	};
	if ( info.version <= 0x14060000 ) {
		NifStream( unknown1, out, info );
		NifStream( unknown2, out, info );
		NifStream( unknown3, out, info );
	};
	if ( info.version >= 0x1E000002 ) {
		NifStream( numColorKeys, out, info );
		for (unsigned int i2 = 0; i2 < colorKeys.size(); i2++) {
			NifStream( colorKeys[i2], out, info, 1 );
		};
		NifStream( colorLoopBehavior, out, info );
		NifStream( numRotationKeys, out, info );
		for (unsigned int i2 = 0; i2 < rotationKeys.size(); i2++) {
			NifStream( rotationKeys[i2], out, info, 1 );
		};
		NifStream( rotationLoopBehavior, out, info );
		NifStream( growTime, out, info );
		NifStream( shrinkTime, out, info );
		NifStream( growGeneration, out, info );
		NifStream( shrinkGeneration, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiPSSimulatorGeneralStep::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiPSSimulatorStep::asString();
	numRotationKeys = (byte)(rotationKeys.size());
	numColorKeys = (byte)(colorKeys.size());
	numSizeKeys = (byte)(sizeKeys.size());
	out << "  Num Size Keys:  " << numSizeKeys << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < sizeKeys.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Size Keys[" << i1 << "]:  " << sizeKeys[i1] << endl;
		array_output_count++;
	};
	out << "  Size Loop Behavior:  " << sizeLoopBehavior << endl;
	out << "  Unknown 1:  " << unknown1 << endl;
	out << "  Unknown 2:  " << unknown2 << endl;
	out << "  Unknown 3:  " << unknown3 << endl;
	out << "  Num Color Keys:  " << numColorKeys << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < colorKeys.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Color Keys[" << i1 << "]:  " << colorKeys[i1] << endl;
		array_output_count++;
	};
	out << "  Color Loop Behavior:  " << colorLoopBehavior << endl;
	out << "  Num Rotation Keys:  " << numRotationKeys << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < rotationKeys.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Rotation Keys[" << i1 << "]:  " << rotationKeys[i1] << endl;
		array_output_count++;
	};
	out << "  Rotation Loop Behavior:  " << rotationLoopBehavior << endl;
	out << "  Grow Time:  " << growTime << endl;
	out << "  Shrink Time:  " << shrinkTime << endl;
	out << "  Grow Generation:  " << growGeneration << endl;
	out << "  Shrink Generation:  " << shrinkGeneration << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiPSSimulatorGeneralStep::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiPSSimulatorStep::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiPSSimulatorGeneralStep::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiPSSimulatorStep::GetRefs();
	return refs;
}

std::list<NiObject *> NiPSSimulatorGeneralStep::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiPSSimulatorStep::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
