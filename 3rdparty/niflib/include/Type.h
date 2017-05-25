/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _TYPE_H_
#define _TYPE_H_

#include <string>
#include "dll_export.h"

using namespace std;
namespace Niflib {

/**
 * Run Time Type Inforamtion Class
 */
class Type {
public:
	NIFLIB_API Type (const string & type_name, const Type * par_type );
	NIFLIB_API ~Type();

	NIFLIB_API string GetTypeName() const;

	NIFLIB_API bool IsSameType ( const Type & compare_to ) const;
	NIFLIB_API bool IsDerivedType ( const Type & compare_to ) const;
	NIFLIB_API bool operator<( const Type & compare_to ) const;
private:
	string name;
	const Type * base_type;
};

}
#endif
