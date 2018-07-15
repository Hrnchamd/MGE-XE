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
#include "../../include/obj/NiMesh.h"
#include "../../include/gen/SphereBV.h"
#include "../../include/gen/MeshData.h"
#include "../../include/gen/SemanticData.h"
#include "../../include/obj/NiDataStream.h"
#include "../../include/gen/ExtraMeshDataEpicMickey.h"
#include "../../include/gen/ExtraMeshDataEpicMickey2.h"
#include "../../include/obj/NiMeshModifier.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiMesh::TYPE("NiMesh", &NiRenderObject::TYPE );

NiMesh::NiMesh() : primitiveType((MeshPrimitiveType)0), unknown51((int)0), unknown52((int)0), unknown53((int)0), unknown54((int)0), unknown55(0.0f), unknown56((int)0), numSubmeshes((unsigned short)0), instancingEnabled(false), numDatas((unsigned int)0), numModifiers((unsigned int)0), unknown100((byte)0), unknown101((int)0), unknown102((unsigned int)0), unknown200((int)0), unknown250((int)0), unknown300((int)0), unknown301((short)0), unknown302((int)0), unknown350((int)0), unknown400((int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

NiMesh::~NiMesh() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & NiMesh::GetType() const {
	return TYPE;
}

NiObject * NiMesh::Create() {
	return new NiMesh;
}

void NiMesh::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	NiRenderObject::Read( in, link_stack, info );
	NifStream( primitiveType, in, info );
	if ( info.userVersion == 15 ) {
		NifStream( unknown51, in, info );
		NifStream( unknown52, in, info );
		NifStream( unknown53, in, info );
		NifStream( unknown54, in, info );
		NifStream( unknown55, in, info );
		NifStream( unknown56, in, info );
	};
	NifStream( numSubmeshes, in, info );
	NifStream( instancingEnabled, in, info );
	NifStream( bound.center, in, info );
	NifStream( bound.radius, in, info );
	NifStream( numDatas, in, info );
	datas.resize(numDatas);
	for (unsigned int i1 = 0; i1 < datas.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
		NifStream( datas[i1].isPerInstance, in, info );
		NifStream( datas[i1].numSubmeshes, in, info );
		datas[i1].submeshToRegionMap.resize(datas[i1].numSubmeshes);
		for (unsigned int i2 = 0; i2 < datas[i1].submeshToRegionMap.size(); i2++) {
			NifStream( datas[i1].submeshToRegionMap[i2], in, info );
		};
		NifStream( datas[i1].numComponents, in, info );
		datas[i1].componentSemantics.resize(datas[i1].numComponents);
		for (unsigned int i2 = 0; i2 < datas[i1].componentSemantics.size(); i2++) {
			NifStream( datas[i1].componentSemantics[i2].name, in, info );
			NifStream( datas[i1].componentSemantics[i2].index, in, info );
		};
	};
	NifStream( numModifiers, in, info );
	modifiers.resize(numModifiers);
	for (unsigned int i1 = 0; i1 < modifiers.size(); i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	if ( info.userVersion == 15 ) {
		NifStream( unknown100, in, info );
		NifStream( unknown101, in, info );
		NifStream( unknown102, in, info );
		unknown103.resize(unknown102);
		for (unsigned int i2 = 0; i2 < unknown103.size(); i2++) {
			NifStream( unknown103[i2], in, info );
		};
		NifStream( unknown200, in, info );
		unknown201.resize(unknown200);
		for (unsigned int i2 = 0; i2 < unknown201.size(); i2++) {
			NifStream( unknown201[i2].unknownInt1, in, info );
			NifStream( unknown201[i2].unknownInt2, in, info );
			NifStream( unknown201[i2].unknownInt3, in, info );
			NifStream( unknown201[i2].unknownInt4, in, info );
			NifStream( unknown201[i2].unknownInt5, in, info );
			NifStream( unknown201[i2].unknownInt6, in, info );
		};
		NifStream( unknown250, in, info );
		unknown251.resize(unknown250);
		for (unsigned int i2 = 0; i2 < unknown251.size(); i2++) {
			NifStream( unknown251[i2], in, info );
		};
		NifStream( unknown300, in, info );
		NifStream( unknown301, in, info );
		NifStream( unknown302, in, info );
		unknown303.resize(unknown302);
		for (unsigned int i2 = 0; i2 < unknown303.size(); i2++) {
			NifStream( unknown303[i2], in, info );
		};
		NifStream( unknown350, in, info );
		unknown351.resize(unknown350);
		for (unsigned int i2 = 0; i2 < unknown351.size(); i2++) {
			NifStream( unknown351[i2].start, in, info );
			NifStream( unknown351[i2].end, in, info );
			for (unsigned int i3 = 0; i3 < 10; i3++) {
				NifStream( unknown351[i2].unknownShorts[i3], in, info );
			};
		};
		NifStream( unknown400, in, info );
	};

	//--BEGIN POST-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiMesh::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiRenderObject::Write( out, link_map, missing_link_stack, info );
	unknown350 = (int)(unknown351.size());
	unknown302 = (int)(unknown303.size());
	unknown250 = (int)(unknown251.size());
	unknown200 = (int)(unknown201.size());
	unknown102 = (unsigned int)(unknown103.size());
	numModifiers = (unsigned int)(modifiers.size());
	numDatas = (unsigned int)(datas.size());
	NifStream( primitiveType, out, info );
	if ( info.userVersion == 15 ) {
		NifStream( unknown51, out, info );
		NifStream( unknown52, out, info );
		NifStream( unknown53, out, info );
		NifStream( unknown54, out, info );
		NifStream( unknown55, out, info );
		NifStream( unknown56, out, info );
	};
	NifStream( numSubmeshes, out, info );
	NifStream( instancingEnabled, out, info );
	NifStream( bound.center, out, info );
	NifStream( bound.radius, out, info );
	NifStream( numDatas, out, info );
	for (unsigned int i1 = 0; i1 < datas.size(); i1++) {
		datas[i1].numComponents = (int)(datas[i1].componentSemantics.size());
		datas[i1].numSubmeshes = (unsigned short)(datas[i1].submeshToRegionMap.size());
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*datas[i1].stream), out );
		} else {
			if ( datas[i1].stream != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(datas[i1].stream) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( datas[i1].stream );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
		NifStream( datas[i1].isPerInstance, out, info );
		NifStream( datas[i1].numSubmeshes, out, info );
		for (unsigned int i2 = 0; i2 < datas[i1].submeshToRegionMap.size(); i2++) {
			NifStream( datas[i1].submeshToRegionMap[i2], out, info );
		};
		NifStream( datas[i1].numComponents, out, info );
		for (unsigned int i2 = 0; i2 < datas[i1].componentSemantics.size(); i2++) {
			NifStream( datas[i1].componentSemantics[i2].name, out, info );
			NifStream( datas[i1].componentSemantics[i2].index, out, info );
		};
	};
	NifStream( numModifiers, out, info );
	for (unsigned int i1 = 0; i1 < modifiers.size(); i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*modifiers[i1]), out );
		} else {
			if ( modifiers[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(modifiers[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( modifiers[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	if ( info.userVersion == 15 ) {
		NifStream( unknown100, out, info );
		NifStream( unknown101, out, info );
		NifStream( unknown102, out, info );
		for (unsigned int i2 = 0; i2 < unknown103.size(); i2++) {
			NifStream( unknown103[i2], out, info );
		};
		NifStream( unknown200, out, info );
		for (unsigned int i2 = 0; i2 < unknown201.size(); i2++) {
			NifStream( unknown201[i2].unknownInt1, out, info );
			NifStream( unknown201[i2].unknownInt2, out, info );
			NifStream( unknown201[i2].unknownInt3, out, info );
			NifStream( unknown201[i2].unknownInt4, out, info );
			NifStream( unknown201[i2].unknownInt5, out, info );
			NifStream( unknown201[i2].unknownInt6, out, info );
		};
		NifStream( unknown250, out, info );
		for (unsigned int i2 = 0; i2 < unknown251.size(); i2++) {
			NifStream( unknown251[i2], out, info );
		};
		NifStream( unknown300, out, info );
		NifStream( unknown301, out, info );
		NifStream( unknown302, out, info );
		for (unsigned int i2 = 0; i2 < unknown303.size(); i2++) {
			NifStream( unknown303[i2], out, info );
		};
		NifStream( unknown350, out, info );
		for (unsigned int i2 = 0; i2 < unknown351.size(); i2++) {
			NifStream( unknown351[i2].start, out, info );
			NifStream( unknown351[i2].end, out, info );
			for (unsigned int i3 = 0; i3 < 10; i3++) {
				NifStream( unknown351[i2].unknownShorts[i3], out, info );
			};
		};
		NifStream( unknown400, out, info );
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::string NiMesh::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiRenderObject::asString();
	unknown350 = (int)(unknown351.size());
	unknown302 = (int)(unknown303.size());
	unknown250 = (int)(unknown251.size());
	unknown200 = (int)(unknown201.size());
	unknown102 = (unsigned int)(unknown103.size());
	numModifiers = (unsigned int)(modifiers.size());
	numDatas = (unsigned int)(datas.size());
	out << "  Primitive Type:  " << primitiveType << endl;
	out << "  Unknown 51:  " << unknown51 << endl;
	out << "  Unknown 52:  " << unknown52 << endl;
	out << "  Unknown 53:  " << unknown53 << endl;
	out << "  Unknown 54:  " << unknown54 << endl;
	out << "  Unknown 55:  " << unknown55 << endl;
	out << "  Unknown 56:  " << unknown56 << endl;
	out << "  Num Submeshes:  " << numSubmeshes << endl;
	out << "  Instancing Enabled:  " << instancingEnabled << endl;
	out << "  Center:  " << bound.center << endl;
	out << "  Radius:  " << bound.radius << endl;
	out << "  Num Datas:  " << numDatas << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < datas.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		datas[i1].numComponents = (int)(datas[i1].componentSemantics.size());
		datas[i1].numSubmeshes = (unsigned short)(datas[i1].submeshToRegionMap.size());
		out << "    Stream:  " << datas[i1].stream << endl;
		out << "    Is Per Instance:  " << datas[i1].isPerInstance << endl;
		out << "    Num Submeshes:  " << datas[i1].numSubmeshes << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < datas[i1].submeshToRegionMap.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Submesh To Region Map[" << i2 << "]:  " << datas[i1].submeshToRegionMap[i2] << endl;
			array_output_count++;
		};
		out << "    Num Components:  " << datas[i1].numComponents << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < datas[i1].componentSemantics.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			out << "      Name:  " << datas[i1].componentSemantics[i2].name << endl;
			out << "      Index:  " << datas[i1].componentSemantics[i2].index << endl;
		};
	};
	out << "  Num Modifiers:  " << numModifiers << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < modifiers.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Modifiers[" << i1 << "]:  " << modifiers[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 100:  " << unknown100 << endl;
	out << "  Unknown 101:  " << unknown101 << endl;
	out << "  Unknown 102:  " << unknown102 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknown103.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 103[" << i1 << "]:  " << unknown103[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 200:  " << unknown200 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknown201.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Unknown Int 1:  " << unknown201[i1].unknownInt1 << endl;
		out << "    Unknown Int 2:  " << unknown201[i1].unknownInt2 << endl;
		out << "    Unknown Int 3:  " << unknown201[i1].unknownInt3 << endl;
		out << "    Unknown Int 4:  " << unknown201[i1].unknownInt4 << endl;
		out << "    Unknown Int 5:  " << unknown201[i1].unknownInt5 << endl;
		out << "    Unknown Int 6:  " << unknown201[i1].unknownInt6 << endl;
	};
	out << "  Unknown 250:  " << unknown250 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknown251.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 251[" << i1 << "]:  " << unknown251[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 300:  " << unknown300 << endl;
	out << "  Unknown 301:  " << unknown301 << endl;
	out << "  Unknown 302:  " << unknown302 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknown303.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 303[" << i1 << "]:  " << unknown303[i1] << endl;
		array_output_count++;
	};
	out << "  Unknown 350:  " << unknown350 << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < unknown351.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		out << "    Start:  " << unknown351[i1].start << endl;
		out << "    End:  " << unknown351[i1].end << endl;
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < 10; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Unknown Shorts[" << i2 << "]:  " << unknown351[i1].unknownShorts[i2] << endl;
			array_output_count++;
		};
	};
	out << "  Unknown 400:  " << unknown400 << endl;
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

void NiMesh::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//

	NiRenderObject::FixLinks( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < datas.size(); i1++) {
		datas[i1].stream = FixLink<NiDataStream>( objects, link_stack, missing_link_stack, info );
	};
	for (unsigned int i1 = 0; i1 < modifiers.size(); i1++) {
		modifiers[i1] = FixLink<NiMeshModifier>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiMesh::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiRenderObject::GetRefs();
	for (unsigned int i1 = 0; i1 < datas.size(); i1++) {
		if ( datas[i1].stream != NULL )
			refs.push_back(StaticCast<NiObject>(datas[i1].stream));
	};
	for (unsigned int i1 = 0; i1 < modifiers.size(); i1++) {
		if ( modifiers[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(modifiers[i1]));
	};
	return refs;
}

std::list<NiObject *> NiMesh::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiRenderObject::GetPtrs();
	for (unsigned int i1 = 0; i1 < datas.size(); i1++) {
	};
	for (unsigned int i1 = 0; i1 < modifiers.size(); i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
