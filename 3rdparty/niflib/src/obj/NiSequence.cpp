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
#include "../../include/obj/NiSequence.h"
#include "../../include/gen/ControllerLink.h"
#include "../../include/obj/NiInterpolator.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiStringPalette.h"
#include "../../include/obj/NiTimeController.h"
#include "../../include/obj/NiTextKeyExtraData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiSequence::TYPE("NiSequence", &NiObject::TYPE );

NiSequence::NiSequence() : textKeys(NULL), unknownInt4((int)0), unknownInt5((int)0), numControlledBlocks((unsigned int)0), unknownInt1((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiSequence::~NiSequence() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiSequence::GetType() const {
	return TYPE;
}

NiObject * NiSequence::Create() {
	return new NiSequence;
}

void NiSequence::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiObject::Read( in, link_stack, info );
	NifStream( name, in, info );
	if ( info.version <= 0x0A010000 ) {
		NifStream( textKeysName, in, info );
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( ( info.version >= 0x14030009 ) && ( info.version <= 0x14030009 ) && ( info.userVersion == 131072 ) ) {
		NifStream( unknownInt4, in, info );
		NifStream( unknownInt5, in, info );
	};
	NifStream( numControlledBlocks, in, info );
	if ( info.version >= 0x0A01006A ) {
		NifStream( unknownInt1, in, info );
	};
	controlledBlocks.resize(numControlledBlocks);
	for (unsigned int i1 = 0; i1 < controlledBlocks.size(); i1++) {
		if ( info.version <= 0x0A010000 ) {
			NifStream( controlledBlocks[i1].targetName, in, info );
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
		if ( info.version >= 0x0A01006A ) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
			NifStream( controlledBlocks[i1].unknownShort0, in, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( (info.userVersion >= 10) ) ) {
			NifStream( controlledBlocks[i1].priority, in, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( block_num, in, info );
			link_stack.push_back( block_num );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].nodeName, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].nodeName, in, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].nodeNameOffset, in, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].propertyType, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].propertyType, in, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].propertyTypeOffset, in, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].controllerType, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].controllerType, in, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].controllerTypeOffset, in, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].variable1, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].variable1, in, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].variable1Offset, in, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].variable2, in, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].variable2, in, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].variable2Offset, in, info );
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSequence::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::Write( out, link_map, missing_link_stack, info );
	numControlledBlocks = (unsigned int)(controlledBlocks.size());
	NifStream( name, out, info );
	if ( info.version <= 0x0A010000 ) {
		NifStream( textKeysName, out, info );
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*textKeys), out );
		} else {
			if ( textKeys != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(textKeys) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( textKeys );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( ( info.version >= 0x14030009 ) && ( info.version <= 0x14030009 ) && ( info.userVersion == 131072 ) ) {
		NifStream( unknownInt4, out, info );
		NifStream( unknownInt5, out, info );
	};
	NifStream( numControlledBlocks, out, info );
	if ( info.version >= 0x0A01006A ) {
		NifStream( unknownInt1, out, info );
	};
	for (unsigned int i1 = 0; i1 < controlledBlocks.size(); i1++) {
		if ( info.version <= 0x0A010000 ) {
			NifStream( controlledBlocks[i1].targetName, out, info );
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*controlledBlocks[i1].controller), out );
			} else {
				if ( controlledBlocks[i1].controller != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(controlledBlocks[i1].controller) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( controlledBlocks[i1].controller );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
		if ( info.version >= 0x0A01006A ) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*controlledBlocks[i1].interpolator), out );
			} else {
				if ( controlledBlocks[i1].interpolator != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(controlledBlocks[i1].interpolator) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( controlledBlocks[i1].interpolator );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*controlledBlocks[i1].controller), out );
			} else {
				if ( controlledBlocks[i1].controller != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(controlledBlocks[i1].controller) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( controlledBlocks[i1].controller );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*controlledBlocks[i1].unknownLink2), out );
			} else {
				if ( controlledBlocks[i1].unknownLink2 != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(controlledBlocks[i1].unknownLink2) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( controlledBlocks[i1].unknownLink2 );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
			NifStream( controlledBlocks[i1].unknownShort0, out, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( (info.userVersion >= 10) ) ) {
			NifStream( controlledBlocks[i1].priority, out, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			if ( info.version < VER_3_3_0_13 ) {
				WritePtr32( &(*controlledBlocks[i1].stringPalette), out );
			} else {
				if ( controlledBlocks[i1].stringPalette != NULL ) {
					map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(controlledBlocks[i1].stringPalette) );
					if (it != link_map.end()) {
						NifStream( it->second, out, info );
						missing_link_stack.push_back( NULL );
					} else {
						NifStream( 0xFFFFFFFF, out, info );
						missing_link_stack.push_back( controlledBlocks[i1].stringPalette );
					}
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( NULL );
				}
			}
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].nodeName, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].nodeName, out, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].nodeNameOffset, out, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].propertyType, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].propertyType, out, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].propertyTypeOffset, out, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].controllerType, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].controllerType, out, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].controllerTypeOffset, out, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].variable1, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].variable1, out, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].variable1Offset, out, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			NifStream( controlledBlocks[i1].variable2, out, info );
		};
		if ( info.version >= 0x14010003 ) {
			NifStream( controlledBlocks[i1].variable2, out, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			NifStream( controlledBlocks[i1].variable2Offset, out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiSequence::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiObject::asString();
	numControlledBlocks = (unsigned int)(controlledBlocks.size());
	out << "  Name:  " << name << endl;
	out << "  Text Keys Name:  " << textKeysName << endl;
	out << "  Text Keys:  " << textKeys << endl;
	out << "  Unknown Int 4:  " << unknownInt4 << endl;
	out << "  Unknown Int 5:  " << unknownInt5 << endl;
	out << "  Num Controlled Blocks:  " << numControlledBlocks << endl;
	out << "  Unknown Int 1:  " << unknownInt1 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < controlledBlocks.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Target Name:  " << controlledBlocks[i1].targetName << endl;
		out << "    Controller:  " << controlledBlocks[i1].controller << endl;
		out << "    Interpolator:  " << controlledBlocks[i1].interpolator << endl;
		out << "    Unknown Link 2:  " << controlledBlocks[i1].unknownLink2 << endl;
		out << "    Unknown Short 0:  " << controlledBlocks[i1].unknownShort0 << endl;
		out << "    Priority:  " << controlledBlocks[i1].priority << endl;
		out << "    String Palette:  " << controlledBlocks[i1].stringPalette << endl;
		out << "    Node Name:  " << controlledBlocks[i1].nodeName << endl;
		out << "    Node Name Offset:  " << controlledBlocks[i1].nodeNameOffset << endl;
		out << "    Property Type:  " << controlledBlocks[i1].propertyType << endl;
		out << "    Property Type Offset:  " << controlledBlocks[i1].propertyTypeOffset << endl;
		out << "    Controller Type:  " << controlledBlocks[i1].controllerType << endl;
		out << "    Controller Type Offset:  " << controlledBlocks[i1].controllerTypeOffset << endl;
		out << "    Variable 1:  " << controlledBlocks[i1].variable1 << endl;
		out << "    Variable 1 Offset:  " << controlledBlocks[i1].variable1Offset << endl;
		out << "    Variable 2:  " << controlledBlocks[i1].variable2 << endl;
		out << "    Variable 2 Offset:  " << controlledBlocks[i1].variable2Offset << endl;
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiSequence::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiObject::FixLinks( objects, link_stack, missing_link_stack, info );
	if ( info.version <= 0x0A010000 ) {
		textKeys = FixLink<NiTextKeyExtraData>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < controlledBlocks.size(); i1++) {
		if ( info.version <= 0x0A010000 ) {
			controlledBlocks[i1].controller = FixLink<NiTimeController>( objects, link_stack, missing_link_stack, info );
		};
		if ( info.version >= 0x0A01006A ) {
			controlledBlocks[i1].interpolator = FixLink<NiInterpolator>( objects, link_stack, missing_link_stack, info );
			controlledBlocks[i1].controller = FixLink<NiTimeController>( objects, link_stack, missing_link_stack, info );
		};
		if ( ( info.version >= 0x0A01006A ) && ( info.version <= 0x0A01006A ) ) {
			controlledBlocks[i1].unknownLink2 = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
		};
		if ( ( info.version >= 0x0A020000 ) && ( info.version <= 0x14000005 ) ) {
			controlledBlocks[i1].stringPalette = FixLink<NiStringPalette>( objects, link_stack, missing_link_stack, info );
		};
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiSequence::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiObject::GetRefs();
	if ( textKeys != NULL )
		refs.push_back(StaticCast<NiObject>(textKeys));
	for (unsigned int i1 = 0; i1 < controlledBlocks.size(); i1++) {
		if ( controlledBlocks[i1].controller != NULL )
			refs.push_back(StaticCast<NiObject>(controlledBlocks[i1].controller));
		if ( controlledBlocks[i1].interpolator != NULL )
			refs.push_back(StaticCast<NiObject>(controlledBlocks[i1].interpolator));
		if ( controlledBlocks[i1].unknownLink2 != NULL )
			refs.push_back(StaticCast<NiObject>(controlledBlocks[i1].unknownLink2));
		if ( controlledBlocks[i1].stringPalette != NULL )
			refs.push_back(StaticCast<NiObject>(controlledBlocks[i1].stringPalette));
	};
	return refs;
}

std::list<NiObject *> NiSequence::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiObject::GetPtrs();
	for (unsigned int i1 = 0; i1 < controlledBlocks.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
string NiSequence::GetName() const {
   return name;
}

void NiSequence::SetName( const string & value ) {
   name = value;
}

string NiSequence::GetTextKeysName() const {
   return textKeysName;
}

void NiSequence::SetTextKeysName( const string & value ) {
   textKeysName = value;
}

Ref<NiTextKeyExtraData > NiSequence::GetTextKeys() const {
   return textKeys;
}

void NiSequence::SetTextKeys( Ref<NiTextKeyExtraData > value ) {
   textKeys = value;
}

vector<ControllerLink > NiSequence::GetControlledBlocks() const {
   return controlledBlocks;
}

void NiSequence::SetControlledBlocks( const vector<ControllerLink >& value ) {
   controlledBlocks = value;
}

//--END CUSTOM CODE--//
