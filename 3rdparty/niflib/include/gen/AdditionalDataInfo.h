/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _ADDITIONALDATAINFO_H_
#define _ADDITIONALDATAINFO_H_

#include "../NIF_IO.h"

namespace Niflib {


/*!  */
struct AdditionalDataInfo {
	/*! Default Constructor */
	NIFLIB_API AdditionalDataInfo();
	/*! Default Destructor */
	NIFLIB_API ~AdditionalDataInfo();
	/*! Copy Constructor */
	NIFLIB_API AdditionalDataInfo( const AdditionalDataInfo & src );
	/*! Copy Operator */
	NIFLIB_API AdditionalDataInfo & operator=( const AdditionalDataInfo & src );
	/*! Type of data in this channel */
	int dataType;
	/*! Number of bytes per element of this channel */
	int numChannelBytesPerElement;
	/*! Total number of bytes of this channel (num vertices times num bytes per element) */
	int numChannelBytes;
	/*!
	 * Number of bytes per element in all channels together. Sum of num channel bytes
	 * per element over all block infos.
	 */
	int numTotalBytesPerElement;
	/*!
	 * Unsure. The block in which this channel is stored? Usually there is only one
	 * block, and so this is zero.
	 */
	int blockIndex;
	/*!
	 * Offset (in bytes) of this channel. Sum of all num channel bytes per element of
	 * all preceeding block infos.
	 */
	int channelOffset;
	/*! Unknown, usually equal to 2. */
	byte unknownByte1;
	//--BEGIN MISC CUSTOM CODE--//
	//--END CUSTOM CODE--//
};

}
#endif
