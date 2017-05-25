/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _ANIM_COLLECTION_H_
#define _ANIM_COLLECTION_H_

#include "niflib.h"
#include "Ref.h"
#include "gen/enums.h"
#include "dll_export.h"
#include "nif_versions.h"
#include <vector>
#include <string>

namespace Niflib {

class AnimSequence;
class NiObject;
class NiTimeController;
class NiTextKeyExtraData;

using namespace std;

vector<AnimSequence> GatherSequences( NiObject * root );

class AnimSequence {
public:
	NIFLIB_API AnimSequence();
	NIFLIB_API ~AnimSequence();
	NIFLIB_API string GetName();
	NIFLIB_API void SetName( const string & name );
	NIFLIB_API CycleType GetCycleType();
	NIFLIB_API void SetCycleType( CycleType type );
	NIFLIB_API float GetStartTime();
	NIFLIB_API void SetStartTime( float time );
	NIFLIB_API float GetStopTime();
	NIFLIB_API void SetStopTime( float time );
	NIFLIB_API float GetWeight();
	NIFLIB_API void SetWeight( float weight );
	NIFLIB_API Ref<NiTextKeyExtraData> GetTextKeys();
	NIFLIB_API void SetTextKeys( NiTextKeyExtraData * keys );

	NIFLIB_API unsigned int GetNumControllers();
	NIFLIB_API string GetAttachNodeName( unsigned int controller_index );
	NIFLIB_API void SetAttachNodeName( unsigned int controller_index, const string & name );

	NIFLIB_API Ref<NiTimeController> GenControllerTree( unsigned int controller_index, unsigned int version = 0xFFFFFFFF );
	
	NIFLIB_API Ref<NiObject> GetControllerData( unsigned int controller_index );

	NIFLIB_API void AddControllerData( NiObject * data );
private:
	string sequence_name;
	CycleType cycle_type;
	float start_time;
	float stop_time;
	float weight;
	Ref< NiTextKeyExtraData > text_keys;

	vector< pair<Ref<NiObject>, string> > controller_data;
};


} //end namespace Niflib

#endif
