/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _NIFLIB_KEY_H_
#define _NIFLIB_KEY_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include "gen/enums.h"

namespace Niflib {
using namespace std;

/*! Stores an animation key and the time in the animation that it takes affect. It is a template class so it can hold any kind of data as different objects key different sorts of information to the animation timeline.*/
template <class T> 
struct Key {
	float time; /*!< The time on the animation timeline that this keyframe takes affect. */ 
	T data; /*!< The data being keyed to the timeline. */ 
	T forward_tangent; /*!< A piece of data of the same type as is being keyed to the time line used as the forward tangent in quadratic interpolation.  Ignored if key type is set as something else. */ 
	T backward_tangent; /*!< A piece of data of the same type as is being keyed to the time line used as the backward tangent in quadratic interpolation.  Ignored if key type is set as something else. */ 
	float tension; /*!< The amount of tension to use in tension, bias, continuity interpolation.  Ignored if key type is something else.*/
	float bias; /*!< The amount of bias to use in tension, bias, continuity interpolation.  Ignored if key type is something else.*/
	float continuity; /*!< The amount of continuity to use in tension, bias, continuity interpolation.  Ignored if key type is something else.*/
};

template <class T> 
ostream & operator<<( ostream & out, Key<T> const & val ) {
	return out << "Time:  " << val.time << endl
			   << "Data:  " << val.data << endl
			   << "Forward Tangent:  " << val.forward_tangent << endl
			   << "Backward Tangent:  " << val.backward_tangent << endl
			   << "Bias:  " << val.bias << endl
			   << "Continuity:  " << val.continuity << endl;
}

/*!
 * A function to normalize the key times in a vector of keys to be in seconds,
 * effectivly setting phase to zero and frequency to 1.
 * \param[in/out] keys The vector of keys to be normalized.
 * \param[in] phase The phase shift to remove during normalization.
 * \param[in] frequency The original frequency of the keys which will be
 * normalized to 1.
 */
template <class T>
void NormalizeKeyVector( vector< Key<T> > & keys, float phase, float frequency ) {
	for ( size_t i = 0; i < keys.size(); ++i ) {
		keys[i].time = ( keys[i].time - phase ) / frequency;
	}
}

/*!
 * A function to extract key values for a certain amount of time.  Values will be
 * duplicated if necessary when cycle_type is CYCLE_LOOP or CYCLE_REVERSE.
 */
template <class T>
vector< Key<T> > ExtractKeySlice( const vector< Key<T> > & keys, float slice_start, float slice_stop, float keys_start, float keys_stop, CycleType cycle = CYCLE_CLAMP ) {
	vector< Key<T> > out;

	//Get first set of keys
	for ( size_t i = 0; i < keys.size(); ++i ) {
		if ( keys[i].time >= slice_start && keys[i].time <= slice_stop ) {
			out.push_back( keys[i] );
		}
	}

	//Get additional keys based on cycle type.
	if ( cycle == CYCLE_LOOP || cycle == CYCLE_REVERSE ) {
		float c = floor( slice_start / (keys_stop - keys_start) ) + 1.0f;
		bool reverse = false;
		bool failed = false;
		while ( failed == false ) {
			if ( cycle == CYCLE_REVERSE ) {
				if ( reverse == false ) {
					reverse = true;
				} else {
					reverse = false;
				}
			}

			int first, last, vec;
			if ( reverse == true ) {
				first = int(keys.size()) - 1;
				last = -1;
				vec = -1;
			} else {
				first = 0;
				last = int(keys.size());
				vec = 1;
			}

			for ( int i = first; i != last; i+=vec ) {
				float time = keys[i].time;
				time = keys_start + ( keys_stop - time ) + c * ( keys_stop - keys_start );

				if ( time >= slice_start && time <= slice_stop ) {
					bool add_key = true;
					size_t prev_key = out.size() - 1;		
					if ( out.size() > 0 && out[prev_key].time == keys[i].time ) {
						add_key = false;
					}
					if ( add_key == true ) {
						out.push_back( keys[i] );
					}
				} else {
					failed = true;
					break;
				}
			}
			c += 1.0;
		}
	}

	return out;
}


} //end namespace Niflib

#endif
