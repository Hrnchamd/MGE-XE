/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//

#include "../../NvTriStrip/NvTriStrip.h"
#include "../../TriStripper/tri_stripper.h"
#include <vector>
#include <list>

using namespace triangle_stripper;
using namespace NvTriStrip;

// Helper methods
typedef std::vector<unsigned short> TriStrip;
typedef	std::list<TriStrip> TriStrips;

//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/NiTriStripsData.h"
using namespace Niflib;

//Definition of TYPE constant
const Type NiTriStripsData::TYPE("NiTriStripsData", &NiTriBasedGeomData::TYPE );

NiTriStripsData::NiTriStripsData() : numStrips((unsigned short)0), hasPoints(false) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

NiTriStripsData::~NiTriStripsData() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

const Type & NiTriStripsData::GetType() const {
	return TYPE;
}

NiObject * NiTriStripsData::Create() {
	return new NiTriStripsData;
}

void NiTriStripsData::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::Read( in, link_stack, info );
	NifStream( numStrips, in, info );
	stripLengths.resize(numStrips);
	for (unsigned int i1 = 0; i1 < stripLengths.size(); i1++) {
		NifStream( stripLengths[i1], in, info );
	};
	if ( info.version >= 0x0A000103 ) {
		NifStream( hasPoints, in, info );
	};
	if ( info.version <= 0x0A000102 ) {
		points.resize(numStrips);
		for (unsigned int i2 = 0; i2 < points.size(); i2++) {
			points[i2].resize(stripLengths[i2]);
			for (unsigned int i3 = 0; i3 < stripLengths[i2]; i3++) {
				NifStream( points[i2][i3], in, info );
			};
		};
	};
	if ( info.version >= 0x0A000103 ) {
		if ( hasPoints ) {
			points.resize(numStrips);
			for (unsigned int i3 = 0; i3 < points.size(); i3++) {
				points[i3].resize(stripLengths[i3]);
				for (unsigned int i4 = 0; i4 < stripLengths[i3]; i4++) {
					NifStream( points[i3][i4], in, info );
				};
			};
		};
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTriStripsData::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::Write( out, link_map, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < points.size(); i1++)
		stripLengths[i1] = (unsigned short)(points[i1].size());
	numStrips = (unsigned short)(stripLengths.size());
	NifStream( numStrips, out, info );
	for (unsigned int i1 = 0; i1 < stripLengths.size(); i1++) {
		NifStream( stripLengths[i1], out, info );
	};
	if ( info.version >= 0x0A000103 ) {
		NifStream( hasPoints, out, info );
	};
	if ( info.version <= 0x0A000102 ) {
		for (unsigned int i2 = 0; i2 < points.size(); i2++) {
			for (unsigned int i3 = 0; i3 < stripLengths[i2]; i3++) {
				NifStream( points[i2][i3], out, info );
			};
		};
	};
	if ( info.version >= 0x0A000103 ) {
		if ( hasPoints ) {
			for (unsigned int i3 = 0; i3 < points.size(); i3++) {
				for (unsigned int i4 = 0; i4 < stripLengths[i3]; i4++) {
					NifStream( points[i3][i4], out, info );
				};
			};
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string NiTriStripsData::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << NiTriBasedGeomData::asString();
	for (unsigned int i1 = 0; i1 < points.size(); i1++)
		stripLengths[i1] = (unsigned short)(points[i1].size());
	numStrips = (unsigned short)(stripLengths.size());
	out << "  Num Strips:  " << numStrips << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < stripLengths.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Strip Lengths[" << i1 << "]:  " << stripLengths[i1] << endl;
		array_output_count++;
	};
	out << "  Has Points:  " << hasPoints << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < points.size(); i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		for (unsigned int i2 = 0; i2 < stripLengths[i1]; i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Points[" << i2 << "]:  " << points[i1][i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void NiTriStripsData::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	NiTriBasedGeomData::FixLinks( objects, link_stack, missing_link_stack, info );

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> NiTriStripsData::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = NiTriBasedGeomData::GetRefs();
	return refs;
}

std::list<NiObject *> NiTriStripsData::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = NiTriBasedGeomData::GetPtrs();
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//

NiTriStripsData::NiTriStripsData(const vector<Triangle> &tris, bool nvtristrips) {
   if (nvtristrips)
      SetNvTriangles(tris);
   else
      SetTSTriangles(tris);
}

unsigned short NiTriStripsData::GetStripCount() const {
	return (unsigned short)(points.size());
}

void NiTriStripsData::SetStripCount(int n) {
	points.resize( n );
   stripLengths.resize( n );
   hasPoints = (n != 0);

	//Recalculate Triangle Count
	numTriangles = CalcTriangleCount();
}

//Getters
vector<unsigned short> NiTriStripsData::GetStrip( int index ) const {
	return points[index];
}

vector<Triangle> NiTriStripsData::GetTriangles() const {

	//Create a vector to hold the triangles
	vector<Triangle> triangles;
	int n = 0; // Current triangle

	//Cycle through all strips
	vector< vector<unsigned short> >::const_iterator it;
	Triangle t;
	for (it = points.begin(); it != points.end(); ++it ) {
		//The first three values in the strip are the first triangle
		t.Set( (*it)[0], (*it)[1], (*it)[2] );

		//Only add triangles to the list if none of the vertices match
		if ( t[0] != t[1] && t[0] != t[2] && t[1] != t[2] ) {
			triangles.push_back(t);
		}

		//Move to the next triangle
		++n;

		//The remaining triangles use the previous two indices as their first two indices.
		for( unsigned int i = 3; i < it->size(); ++i ) {
			//Odd numbered triangles need to be reversed to keep the vertices in counter-clockwise order
			if ( i % 2 == 0 ) {
				t.Set( (*it)[i - 2], (*it)[i - 1], (*it)[i] );
			} else {
				t.Set( (*it)[i], (*it)[i - 1], (*it)[i - 2] );
			}

			//Only add triangles to the list if none of the vertices match
			if ( t[0] != t[1] && t[0] != t[2] && t[1] != t[2] ) {
				triangles.push_back(t);
			}

			//Move to the next triangle
			++n;
		}
	}

	return triangles;
}

//Setter
void NiTriStripsData::SetStrip( int index, const vector<unsigned short> & in ) {
	points[index] = in;

	//Recalculate Triangle Count
	numTriangles = CalcTriangleCount();
}

unsigned short NiTriStripsData::CalcTriangleCount() const {

	//Calculate number of triangles
	//Sum of length of each strip - 2
	unsigned short numTriangles = 0;
	for ( unsigned int i = 0; i < points.size(); ++i ) {
		numTriangles += (unsigned short)(points[i].size() - 2);
	}

	return numTriangles;
}

void NiTriStripsData::SetTriangles( const vector<Triangle> & in ) {
   SetNvTriangles(in);
}

void NiTriStripsData::SetNvTriangles( const vector<Triangle> & in ) {
   if ( in.size() > 65535 || in.size() < 0 ) {
      throw runtime_error("Invalid Triangle Count: must be between 0 and 65535.");
   }
   points.clear();
   numTriangles = 0;

   unsigned short *data = new unsigned short[in.size() * 3 * 2];
   for (size_t i=0; i< in.size(); i++) {
      data[i * 3 + 0] = in[i][0];
      data[i * 3 + 1] = in[i][1];
      data[i * 3 + 2] = in[i][2];
   }

   PrimitiveGroup * groups = 0;
   unsigned short numGroups = 0;

   // GF 3+
   SetCacheSize(CACHESIZE_GEFORCE3);
   // don't generate hundreds of strips
   SetStitchStrips(true);
   GenerateStrips(data, int(in.size()*3), &groups, &numGroups);

   delete [] data;

   if (!groups)
      return;

   SetStripCount(numGroups);
   for (int g=0; g<numGroups; g++) {
      if (groups[g].type == PT_STRIP) {
         vector<unsigned short> strip(groups[g].numIndices);
         for (unsigned int s=0; s<groups[g].numIndices; s++)
            strip[s] = groups[g].indices[s];
         SetStrip(g, strip);
      }
   }
   delete [] groups;

   //Recalculate Triangle Count
   numTriangles = CalcTriangleCount();
}

void NiTriStripsData::SetTSTriangles( const vector<Triangle> & in ) {
   if ( in.size() > 65535 || in.size() < 0 ) {
      throw runtime_error("Invalid Triangle Count: must be between 0 and 65535.");
   }

   points.clear();
   numTriangles = 0;

   TriStrips strips;
   triangle_stripper::indices idcs(in.size()*3);
   size_t i, j;
   for (i=0; i<in.size(); i++)
   {
      idcs[i * 3 + 0] = in[i][0];
      idcs[i * 3 + 1] = in[i][1];
      idcs[i * 3 + 2] = in[i][2];
   }

   tri_stripper stripper(idcs);

   primitive_vector groups;
   stripper.Strip(&groups);

   // triangles left over
   vector<Triangle> stris;

   for (i=0; i<groups.size(); i++)
   {
      if (groups[i].Type == TRIANGLE_STRIP)
      {			
         strips.push_back( TriStrip( (unsigned short)(groups[i].Indices.size()) ) );
         TriStrip &strip = strips.back();

         for (j=0; j<groups[i].Indices.size(); j++)
            strip[j] = groups[i].Indices[j];
      } else
      {
         size_t size = stris.size();
         stris.resize(size + groups[i].Indices.size()/3);
         for (j=(size>0)?(size-1):0; j<stris.size(); j++)
         {
            stris[j][0] = groups[i].Indices[j*3+0];
            stris[j][1] = groups[i].Indices[j*3+1];
            stris[j][2] = groups[i].Indices[j*3+2];
         }
      }
   }

   if (stris.size())
   {
      // stitch em
      TriStrip strip;
      if (strips.size() > 0)
      {
         strip.push_back(strips.back()[strips.back().size()-1]);
         strip.push_back(stris[0][0]);
      }
      for (i=0; i<stris.size(); i++)
      {
         if (i > 0)
         {
            strip.push_back(stris[i][0]);
            strip.push_back(stris[i][0]);
         }

         strip.push_back(stris[i][0]);
         strip.push_back(stris[i][1]);
         strip.push_back(stris[i][2]);
         if (i < stris.size()-1)
            strip.push_back(stris[i][2]);
      }
      strips.push_back(strip);
   }

   if (strips.size() > 0)
   {
      SetStripCount( int(strips.size()) );

      int i = 0;
      TriStrips::const_iterator it;
      for (it=strips.begin(); it!=strips.end(); ++it)
         SetStrip(i++, *it);
   }

   //Recalculate Triangle Count
   numTriangles = CalcTriangleCount();
}

//--END CUSTOM CODE--//
