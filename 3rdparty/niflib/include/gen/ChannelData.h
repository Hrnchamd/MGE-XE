/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _CHANNELDATA_H_
#define _CHANNELDATA_H_

#include "../NIF_IO.h"

namespace Niflib {


/*! Channel data */
struct ChannelData {
	/*! Default Constructor */
	NIFLIB_API ChannelData();
	/*! Default Destructor */
	NIFLIB_API ~ChannelData();
	/*! Copy Constructor */
	NIFLIB_API ChannelData( const ChannelData & src );
	/*! Copy Operator */
	NIFLIB_API ChannelData & operator=( const ChannelData & src );
	/*! Channel Type */
	ChannelType type;
	/*! Data Storage Convention */
	ChannelConvention convention;
	/*! Bits per channel */
	byte bitsPerChannel;
	/*! Unknown */
	byte unknownByte1;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
