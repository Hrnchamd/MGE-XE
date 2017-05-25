/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/Key.h"
#include "../include/AnimSequence.h"
#include "../include/obj/NiObject.h"
#include "../include/obj/NiTextKeyExtraData.h"
#include "../include/obj/NiTimeController.h"



using namespace Niflib;



vector<AnimSequence> GatherSequences( NiObject * root ) {

	return vector<AnimSequence>();
}

AnimSequence::AnimSequence() {}

AnimSequence::~AnimSequence() {}

string AnimSequence::GetName() {
	return sequence_name;
}

void AnimSequence::SetName( const string & name ) {
	sequence_name = name;
}

CycleType AnimSequence::GetCycleType() {
	return cycle_type;
}

void AnimSequence::SetCycleType( CycleType type ) {
	cycle_type = type;
}

float AnimSequence::GetStartTime() {
	return start_time;
}

void AnimSequence::SetStartTime( float time ) {
	start_time = time;
}

float AnimSequence::GetStopTime() {
	return stop_time;
}


void AnimSequence::SetStopTime( float time ) {
	
}

float AnimSequence::GetWeight() {
	return this->weight;
}

void AnimSequence::SetWeight( float weight ) {
	this->weight = weight;
}


Ref<NiTextKeyExtraData> AnimSequence::GetTextKeys() {
	return text_keys;
}

void AnimSequence::SetTextKeys( NiTextKeyExtraData * keys ) {
	text_keys = keys;
}

unsigned int AnimSequence::GetNumControllers() {
	return controller_data.size();
}

string AnimSequence::GetAttachNodeName( unsigned int controller_index ) {
	if ( controller_index > controller_data.size() ) {
		throw( "An out of bounds index was passed to AnimSequence::GetAttachNodeName" );
	}

	return controller_data[controller_index].second;
}

void AnimSequence::SetAttachNodeName( unsigned int controller_index, const string & name ) {
	if ( controller_index > controller_data.size() ) {
		throw( "An out of bounds index was passed to AnimSequence::SetAttachNodeName" );
	}

	controller_data[controller_index].second = name;
}

Ref<NiTimeController> AnimSequence::GenControllerTree( unsigned int controller_index, unsigned int version ) {
	return NiTimeControllerRef();
}

Ref<NiObject> AnimSequence::GetControllerData( unsigned int controller_index ) {
	return NiObjectRef();
}

void AnimSequence::AddControllerData( NiObject * data ) {
	
}

