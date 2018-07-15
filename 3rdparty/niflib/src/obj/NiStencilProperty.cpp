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
#include "../../include/obj/NiStencilProperty.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiStencilProperty::TYPE("NiStencilProperty", &NiProperty::TYPE );

NiStencilProperty::NiStencilProperty() : flags((unsigned short)0), stencilEnabled((byte)0), stencilFunction((StencilCompareMode)0), stencilRef((unsigned int)0), stencilMask((unsigned int)4294967295), failAction((StencilAction)0), zFailAction((StencilAction)0), passAction((StencilAction)0), drawMode((FaceDrawMode)DRAW_BOTH) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiStencilProperty::~NiStencilProperty() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiStencilProperty::GetType() const {
	return TYPE;
}

NiObject * NiStencilProperty::Create() {
	return new NiStencilProperty;
}

void NiStencilProperty::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Read( in, link_stack, info );
	if ( info.version <= 0x0A000102 ) {
		NifStream( flags, in, info );
	};
	if ( info.version <= 0x14000005 ) {
		NifStream( stencilEnabled, in, info );
		NifStream( stencilFunction, in, info );
		NifStream( stencilRef, in, info );
		NifStream( stencilMask, in, info );
		NifStream( failAction, in, info );
		NifStream( zFailAction, in, info );
		NifStream( passAction, in, info );
		NifStream( drawMode, in, info );
	};
	if ( info.version >= 0x14010003 ) {
		NifStream( flags, in, info );
		NifStream( stencilRef, in, info );
		NifStream( stencilMask, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiStencilProperty::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::Write( out, link_map, missing_link_stack, info );
	if ( info.version <= 0x0A000102 ) {
		NifStream( flags, out, info );
	};
	if ( info.version <= 0x14000005 ) {
		NifStream( stencilEnabled, out, info );
		NifStream( stencilFunction, out, info );
		NifStream( stencilRef, out, info );
		NifStream( stencilMask, out, info );
		NifStream( failAction, out, info );
		NifStream( zFailAction, out, info );
		NifStream( passAction, out, info );
		NifStream( drawMode, out, info );
	};
	if ( info.version >= 0x14010003 ) {
		NifStream( flags, out, info );
		NifStream( stencilRef, out, info );
		NifStream( stencilMask, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiStencilProperty::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	out << NiProperty::asString();
	out << "  Flags:  " << flags << endl;
	out << "  Stencil Enabled:  " << stencilEnabled << endl;
	out << "  Stencil Function:  " << stencilFunction << endl;
	out << "  Stencil Ref:  " << stencilRef << endl;
	out << "  Stencil Mask:  " << stencilMask << endl;
	out << "  Fail Action:  " << failAction << endl;
	out << "  Z Fail Action:  " << zFailAction << endl;
	out << "  Pass Action:  " << passAction << endl;
	out << "  Draw Mode:  " << drawMode << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiStencilProperty::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiProperty::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiStencilProperty::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiProperty::GetRefs();
	return refs;
}

std::list<NiObject *> NiStencilProperty::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiProperty::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

unsigned short NiStencilProperty::GetFlags() const {
   return flags;
}

void NiStencilProperty::SetFlags(unsigned short value) {
   flags = value;
}

bool NiStencilProperty::GetStencilState() const {
   return (stencilEnabled != 0);
}

void NiStencilProperty::SetStencilState(bool value) {
   stencilEnabled = value;
}

StencilCompareMode NiStencilProperty::GetStencilFunction() const {
   return stencilFunction;
}

void NiStencilProperty::SetStencilFunction(StencilCompareMode value) {
   stencilFunction = value;
}

unsigned int NiStencilProperty::GetStencilRef() const {
   return stencilRef;
}

void NiStencilProperty::SetStencilRef(unsigned int value) {
   stencilRef = value;
}

unsigned int NiStencilProperty::GetStencilMask() const {
   return stencilMask;
}

void NiStencilProperty::SetStencilMask(unsigned int value) {
   stencilMask = value;
}

StencilAction NiStencilProperty::GetFailAction() const {
   return failAction;
}

void NiStencilProperty::SetFailAction(StencilAction value) {
   failAction = value;
}

StencilAction NiStencilProperty::GetZFailAction() const {
   return zFailAction;
}

void NiStencilProperty::SetZFailAction(StencilAction value) {
   zFailAction = value;
}

StencilAction NiStencilProperty::GetPassAction() const {
   return passAction;
}

void NiStencilProperty::SetPassAction(StencilAction value) {
   passAction = value;
}

FaceDrawMode NiStencilProperty::GetFaceDrawMode() const {
   return drawMode;
}

void NiStencilProperty::SetFaceDrawMode(FaceDrawMode value) {
   drawMode = value;
}

//--END CUSTOM CODE--//
