/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _DLL_EXPORT_H_
#define _DLL_EXPORT_H_

// detect visibility support for linux compilers
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif


#ifndef NIFLIB_STATIC_LINK
	// Building shared library
	#if defined(_WIN32) || defined(__WIN32__) || defined(_MSC_VER)
		// Windows
		#ifdef BUILDING_NIFLIB_DLL
			//The building process is underway, export symbols
			#define NIFLIB_API __declspec(dllexport)
		#else
			//Header files are being used to import symbols from a previously built library
			#define NIFLIB_API __declspec(dllimport)
		#endif
		#define NIFLIB_HIDDEN
	#elif defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
		// Linux (GCC)
		#define NIFLIB_API __attribute__ ((visibility("default")))
		#define NIFLIB_HIDDEN __attribute__ ((visibility("hidden")))
	#else
		#error __attribute__ ((visibility("hidden"))) support required, but not detected (see gcc.gnu.org/wiki/Visibility)
	#endif
#else
	// Building static library
	#define NIFLIB_API
	#define NIFLIB_HIDDEN
#endif

#endif
