/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef NIF_MATH_H
#define NIF_MATH_H

#include <cmath>
#include <cstring> // memcpy has been moved in GCC 4.3
#include <iostream>
#include <stdexcept>
#include "dll_export.h"

using namespace std;
namespace Niflib {

#ifndef PI
#define PI 3.14159265358979323846f  //Probably more accurate than a float can be, but it will just be rounded off anyway
#endif

#ifndef _countof
#define _countof(x) (int)((sizeof (x))/(sizeof((x)[0])))
#endif

//Forward declarations
struct TexCoord;
struct Triangle;
struct Vector3;
struct Vector4;
struct Color3;
struct Color4;
struct Quaternion;
struct Float2;
struct Matrix22;
struct Float3;
struct Matrix33;
struct Float4;
struct Matrix44;
struct InertiaMatrix;

/*! Stores 2D texture coordinates as two floating point variables, u and v. */
struct TexCoord {
	float u; /*!< The U value in this coordinate pair. */ 
	float v; /*!< The V value in this coordinate pair. */ 

	/*! Default constructor	*/
	NIFLIB_API TexCoord() : u(0.0f), v(0.0f) {}

	/*! Copy constructor	*/
	NIFLIB_API TexCoord(const TexCoord& src) : u(src.u), v(src.v) {}

	NIFLIB_API TexCoord operator+(const TexCoord& rhs) const
	{
		TexCoord ret;
		ret = *this;
		ret.u += rhs.u;
		ret.v += rhs.v;
		return ret;
	}

	NIFLIB_API TexCoord operator-(const TexCoord& rhs) const
	{
		TexCoord ret;
		ret = *this;
		ret.u -= rhs.u;
		ret.v -= rhs.v;
		return ret;
	}

	NIFLIB_API TexCoord operator*(const float rhs) const
	{
		TexCoord ret;
		ret = *this;
		ret.u *= rhs;
		ret.v *= rhs;
		return ret;
	}

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] u The value to set U to.
	 * \param[in] v The value to set V to.
	 */
	NIFLIB_API TexCoord(float u, float v) {
		this->u = u;
		this->v = v;
	}

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] u The value to set U to.
	 * \param[in] v The value to set V to.
	 */
	NIFLIB_API void Set(float u, float v) {
		this->u = u;
		this->v = v;
	}

	bool operator==( const TexCoord & n ) const;
};

/*! Represents a triangle face formed between three vertices referenced by number */
struct Triangle {
	unsigned short v1; /*!< The index of the first vertex. */ 
	unsigned short v2; /*!< The index of the second vertex. */ 
	unsigned short v3; /*!< The index of the third vertex. */ 

	/*! Default constructor */
	NIFLIB_API Triangle() {}

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] v1 The index of the first vertex.
	 * \param[in] v2 The index of the second vertex.
	 * \param[in] v3 The index of the third vertex.
	 */
	NIFLIB_API Triangle(unsigned short v1, unsigned short v2, unsigned short v3) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] v1 The index of the first vertex.
	 * \param[in] v2 The index of the second vertex.
	 * \param[in] v3 The index of the third vertex.
	 */
	NIFLIB_API void Set(unsigned short v1, unsigned short v2, unsigned short v3) {
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	 * \param[in] n The index into the data array.  Should be 0, 1, or 2.
	 * \return The value at the given array index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API unsigned short & operator[](int n) {
		switch (n) {
			case 0: return v1; break;
			case 1: return v2; break;
			case 2: return v3; break;
			default: throw std::out_of_range("Index out of range for Triangle");
		};
	}
	NIFLIB_API unsigned short operator[](int n) const {
		switch (n) {
			case 0: return v1; break;
			case 1: return v2; break;
			case 2: return v3; break;
			default: throw std::out_of_range("Index out of range for Triangle");
		};
	}
};

/*!Represents a position or direction in 3D space*/
struct Vector3 {
	float x; /*!< The X component of this vector. */ 
	float y; /*!< The Y component of this vector. */ 
	float z; /*!< The Z component of this vector. */ 

	/*!Default constructor.*/
	NIFLIB_API Vector3() { x = y = z = 0.0f; }

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] x The value to set X to.
	 * \param[in] y The value to set Y to.
	 * \param[in] z The value to set Z to.
	 */
	NIFLIB_API Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/*! This constructor can be used to initialize this Vector3 with another Vector3
	 * \param[in] v The Vector3 to construct this one from
	 */
	NIFLIB_API Vector3( const Vector3 & v) { x = v.x; y = v.y; z = v.z; }
	
	/*! Destructor */
	NIFLIB_API ~Vector3() {}

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] x The value to set X to.
	 * \param[in] y The value to set Y to.
	 * \param[in] z The value to set Z to.
	 */
	NIFLIB_API void Set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/* This function calculates the magnitude of this vector
	 * \return the magnitude of the vector; its length.
	 */
	NIFLIB_API float Magnitude() const;

	/* This function returns a normalization of this vector.  A vector pointing in the same
	 * direction but with a magnitude, or length, of 1.
	 */
	NIFLIB_API Vector3 Normalized() const;

	/* Allows the addition of vectors.  Each component, x, y, y, is added with
	 * the same component of the other vector.
	 * \return The result of the addition.
	 */
	NIFLIB_API Vector3 operator+( const Vector3 & rh ) const;
	NIFLIB_API Vector3 operator+( const float & rh ) const;

	/* Adds the two vectors and then sets the result to the left-hand vector.
	 * \return This vector is returned.
	 */
	NIFLIB_API Vector3 & operator+=( const Vector3 & rh );
	NIFLIB_API Vector3 & operator+=( const float & rh );

	/* Allows the subtraction of vectors.  Each component, x, y, y, is subtracted from
	 * the same component of the other vector.
	 * \return The result of the subtraction.
	 */
	NIFLIB_API Vector3 operator-( const Vector3 & rh ) const;
	NIFLIB_API Vector3 operator-( const float & rh ) const;

	/* This operator subtracts the two vectors and then sets the result to the left-hand vector.
	 * \return This vector is returned.
	 */
	NIFLIB_API Vector3 & operator-=( const Vector3 & rh);
	NIFLIB_API Vector3 & operator-=( const float & rh );

	/* Allows scaler multiplication, that is multipying all components of the
	 * vector, x, y and z, by the same number.
	 * \return The result of the multiplication.
	 */
	NIFLIB_API Vector3 operator*( const float & rh) const; //Scalar Multiply

	/* Multipies a vector by a scalar and then sets the result to the left-hand vector.
	 * \return This vector is returned.
	 */
	NIFLIB_API Vector3 & operator*=( const float & rh );

	/* Multiplies a vector by a vector using the dot product
	 * \return The dot product of the two vectors.
	 */
	NIFLIB_API float operator*( const Vector3 & v ) const;

	/* Multiplies a vector by a vector using the cross product
	 * \return The cross product of the two vectors.
	 */
	NIFLIB_API Vector3 operator^( const Vector3 & v ) const;

	/* Allows scaler division, that is dividing all components of the
	 * vector, x, y and z, by the same number.
	 * \return The result of the division.
	 */
	NIFLIB_API Vector3 operator/( const float & rh ) const;

	/* Divides a vector by a scalar and then sets the result to the left-hand vector.
	 * \return This vector is returned.
	 */
	NIFLIB_API Vector3 & operator/=( const float & rh );

	/* Sets the components of this Vector3 to those of another Vector3 
	 * \return This vector is returned.
	 */
	NIFLIB_API Vector3 & operator=( const Vector3 & v ) { x = v.x; y = v.y; z = v.z;  return *this; }

	/* Tests the equality of two Vector3 structures.  Vectors are considered equal if all
	 * three components are equal.
	 */
	NIFLIB_API bool operator==( const Vector3 & rh ) const;

	/* Tests the inequality of two Vector3 structures.  Vectors are considered equal if all
	 * three components are equal.
	 */
	NIFLIB_API bool operator!=( const Vector3 & rh ) const;

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	* \param[in] n The index into the data array.  Should be 0, 1, or 2.
	* \return The value at the given array index by reference so it can be read or set via the bracket operator.
	*/
	NIFLIB_API float & operator[](int n);
	NIFLIB_API float operator[](int n) const;

	/* Computes the dot product of two vectors; the angle between two vectors.
	 * \param[in] rh The vector to perform the dot product with
	 * \return The angle in radians between this vector and the one given
	 */
	NIFLIB_API float DotProduct( const Vector3 & rh ) const;

	/* Computes the cross product of two vectors; a vector perpendicular to both of them.
	 * \param[in] The vector to perform the cross product with
	 * \return A vector perpendicular to this vector and the one given
	 */
	NIFLIB_API Vector3 CrossProduct( const Vector3 & rh) const; //Cross Product


	///* Multiplies this Vector with a 4x4 matrix
	// * \param[in] The 4x4 matrix to multiply this vector with. 
	// * \return The new vector resulting from the multiplication.
	// */
	//Vector3 operator*( const Matrix44 & rh ) const;

	///* Multiplies this Vector with a 4x4 matrix and sets the result to itself
	// * \param[in] The 4x4 matrix to multiply this vector with.
	// * \return This vector is returned.
	// */
	//Vector3 & operator*=( const Matrix44 & rh );
};

/*!Represents a position or direction in 3D space*/
struct Vector4 {
	float x; /*!< The X component of this vector. */ 
	float y; /*!< The Y component of this vector. */ 
	float z; /*!< The Z component of this vector. */ 
	float w; /*!< The W component of this vector. */ 

	/*!Default constructor.*/
	NIFLIB_API Vector4() { x = y = z = w = 0.0f; }

	/*! This constructor can be used to set all values in this structure during initialization
	* \param[in] x The value to set X to.
	* \param[in] y The value to set Y to.
	* \param[in] z The value to set Z to.
	* \param[in] w The value to set W to.
	*/
	NIFLIB_API Vector4(float x, float y, float z, float w = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	/*! This constructor can be used to initialize this Vector4 with another Vector4
	* \param[in] v The Vector4 to construct this one from
	*/
	NIFLIB_API Vector4( const Vector4 & v) { x = v.x; y = v.y; z = v.z; w = v.w;}

	/*! This constructor can be used to initialize this Vector4 with a Vector3
	* \param[in] v The Vector3 to construct this one from
	*/
	NIFLIB_API Vector4( const Vector3 & v) { x = v.x; y = v.y; z = v.z; w = 0.0f;}

	/*! This constructor can be used to initialize this Vector4 with a Float4
	* \param[in] v The Float4 to construct this one from
	*/
	NIFLIB_API Vector4( const Float4 & v);

	/*! Destructor */
	NIFLIB_API ~Vector4() {}

	/*! This function can be used to set all values in the structure at the same time.
	* \param[in] x The value to set X to.
	* \param[in] y The value to set Y to.
	* \param[in] z The value to set Z to.
	* \param[in] w The value to set W to.
	*/
	NIFLIB_API void Set(float x, float y, float z, float w = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	/* This function calculates the magnitude of this vector
	* \return the magnitude of the vector; its length.
	*/
	NIFLIB_API float Magnitude() const;

	/* This function returns a normalization of this vector.  A vector pointing in the same
	* direction but with a magnitude, or length, of 1.
	*/
	NIFLIB_API Vector4 Normalized() const;

	/* Allows the addition of vectors.  Each component, x, y, z, w is added with
	* the same component of the other vector.
	* \return The result of the addition.
	*/
	NIFLIB_API Vector4 operator+( const Vector4 & rh ) const;

	/* Adds the two vectors and then sets the result to the left-hand vector.
	* \return This vector is returned.
	*/
	NIFLIB_API Vector4 & operator+=( const Vector4 & rh );

	/* Allows the subtraction of vectors.  Each component, x, y, y, is subtracted from
	* the same component of the other vector.
	* \return The result of the subtraction.
	*/
	NIFLIB_API Vector4 operator-( const Vector4 & rh ) const;

	/* This operator subtracts the two vectors and then sets the result to the left-hand vector.
	* \return This vector is returned.
	*/
	NIFLIB_API Vector4 & operator-=( const Vector4 & rh);

	/* Allows scaler multiplication, that is multiplying all components of the
	* vector, x, y and z, by the same number.
	* \return The result of the multiplication.
	*/
	NIFLIB_API Vector4 operator*( const float & rh) const; //Scalar Multiply

	/* Multiplies a vector by a scalar and then sets the result to the left-hand vector.
	* \return This vector is returned.
	*/
	Vector4 & operator*=( const float & rh );

	/* Multiplies a vector by a vector using the dot product
	* \return The dot product of the two vectors.
	*/
	NIFLIB_API float operator*( const Vector4 & v ) const;

	/* Multiplies a vector by a vector using the cross product
	* \return The cross product of the two vectors.
	*/
	NIFLIB_API Vector4 operator^( const Vector4 & v ) const;

	/* Allows scaler division, that is dividing all components of the
	* vector, x, y and z, by the same number.
	* \return The result of the division.
	*/
	NIFLIB_API Vector4 operator/( const float & rh ) const;

	/* Divides a vector by a scalar and then sets the result to the left-hand vector.
	* \return This vector is returned.
	*/
	Vector4 & operator/=( const float & rh );

	/* Sets the components of this Vector4 to those of another Vector4 
	* \return This vector is returned.
	*/
	NIFLIB_API Vector4 & operator=( const Vector4 & v ) { x = v.x; y = v.y; z = v.z; w = v.w;  return *this; }

	/* Tests the equality of two Vector4 structures.  Vectors are considered equal if all
	* three components are equal.
	*/
	NIFLIB_API bool operator==( const Vector4 & rh ) const;

	/* Tests the inequality of two Vector4 structures.  Vectors are considered equal if all
	* three components are equal.
	*/
	NIFLIB_API bool operator!=( const Vector4 & rh ) const;

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	* \param[in] n The index into the data array.  Should be 0, 1, 2, or 3.
	* \return The value at the given array index by reference so it can be read or set via the bracket operator.
	*/
	NIFLIB_API float & operator[](int n);

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	* \param[in] n The index into the data array.  Should be 0, 1, 2, or 3.
	* \return The value at the given array index by reference so it can be read or set via the bracket operator.
	*/
	NIFLIB_API float operator[](int n) const;

};

/* Stores two floating point numbers.  Used as a row of a Matrix22 */
struct Float2 {
	float data[2]; /*!< The two floating point numbers stored as an array. */ 
	
	/*! The bracket operator makes it possible to use this structure like a C++ array.
	 * \param[in] n The index into the data array.  Should be 0 or 1.
	 * \return The value at the given array index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API float & operator[](int n) {
		return data[n];
	}

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	 * \param[in] n The index into the data array.  Should be 0 or 1.
	 * \return The value at the given array index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API float operator[](int n) const {
		return data[n];
	}

	/*! Default constructor. */
	NIFLIB_API Float2() {}

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] f1 The value to set the first floating point number to.
	 * \param[in] f2 The value to set the second floating point number to.
	 */
	NIFLIB_API Float2( float f1, float f2 ) {
		data[0] = f1;
		data[1] = f2;
	}

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] f1 The value to set the first floating point number to.
	 * \param[in] f2 The value to set the second floating point number to.
	 */
	NIFLIB_API void Set( float f1, float f2 ) {
		data[0] = f1;
		data[1] = f2;
	}
};

/*! Stores a 2 by 2 matrix used for bump maps. */
struct Matrix22 {
	/*! The 2x2 identity matrix constant */
	NIFLIB_API static const Matrix22 IDENTITY;

	Float2 rows[2];  /*!< The two rows of Float2 structures which hold two floating point numbers each. */ 

	/*! The bracket operator makes it possible to use this structure like a 2x2 C++ array.
	 * \param[in] n The index into the row array.  Should be 0 or 1.
	 * \return The Float2 structure for the given row index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API Float2 & operator[](int n) {
		return rows[n];
	}
	NIFLIB_API const Float2 & operator[](int n) const {
		return rows[n];
	}

	/*! Default Constructor */
	NIFLIB_API Matrix22();

	/*! This constructor can be used to set all values in this matrix during initialization
	 * \param[in] m11 The value to set at row 1, column 1.
	 * \param[in] m12 The value to set at row 1, column 2.
	 * \param[in] m21 The value to set at row 2, column 1.
	 * \param[in] m22 The value to set at row 2, column 2.
	 */
	NIFLIB_API Matrix22(
		float m11, float m12,
		float m21, float m22
	) {
		rows[0][0] = m11; rows[0][1] = m12;
		rows[1][0] = m21; rows[1][1] = m22;
	}

	/*! This function can be used to set all values in this matrix at the same time.
	 * \param[in] m11 The value to set at row 1, column 1.
	 * \param[in] m12 The value to set at row 1, column 2.
	 * \param[in] m21 The value to set at row 2, column 1.
	 * \param[in] m22 The value to set at row 2, column 2.
	 */
	NIFLIB_API void Set(
		float m11, float m12,
		float m21, float m22
	) {
		rows[0][0] = m11; rows[0][1] = m12;
		rows[1][0] = m21; rows[1][1] = m22;
	}
};

/* Stores three floating point numbers.  Used as a row of a Matrix33 and to store the data in attr_vector3 and attr_color3 type attributes. */
struct Float3 {
	float data[3]; /*!< The three floating point numbers stored as an array. */ 

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	 * \param[in] n The index into the data array.  Should be 0, 1, or 2.
	 * \return The value at the given array index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API float & operator[](int n) {
		return data[n];
	}

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	 * \param[in] n The index into the data array.  Should be 0, 1, or 2.
	 * \return The value at the given array index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API float operator[](int n) const {
		return data[n];
	}

	/*!Default constructor.*/
	NIFLIB_API Float3() {}

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] f1 The value to set the first floating point number to.
	 * \param[in] f2 The value to set the second floating point number to.
	 * \param[in] f3 The value to set the third floating point number to.
	 */
	NIFLIB_API Float3( float f1, float f2, float f3 ) {
		data[0] = f1;
		data[1] = f2;
		data[2] = f3;
	}

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] f1 The value to set the first floating point number to.
	 * \param[in] f2 The value to set the second floating point number to.
	 * \param[in] f3 The value to set the third floating point number to.
	 */
	NIFLIB_API void Set( float f1, float f2, float f3 ) {
		data[0] = f1;
		data[1] = f2;
		data[2] = f3;
	}
};

/*! Stores a 3 by 3 matrix used for rotation. */
struct Matrix33 {
	/*! The 3x3 identity matrix constant*/
	NIFLIB_API static const Matrix33 IDENTITY;

	Float3 rows[3]; /*!< The three rows of Float3 structures which hold three floating point numbers each. */ 
	
	/*! The bracket operator makes it possible to use this structure like a 3x3 C++ array.
	 * \param[in] n The index into the row array.  Should be 0, 1, or 2.
	 * \return The Float3 structure for the given row index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API Float3 & operator[](int n) {
		return rows[n];
	}
	NIFLIB_API const Float3 & operator[](int n) const {
		return rows[n];
	}

	/*! Default constructor.   Initializes matrix to identity.  */
	NIFLIB_API Matrix33();

	/*! Copy constructor.   */
	NIFLIB_API Matrix33(const Matrix33& src);

	/*! This constructor can be used to set all values in this matrix during initialization
	 * \param[in] m11 The value to set at row 1, column 1.
	 * \param[in] m12 The value to set at row 1, column 2.
	 * \param[in] m13 The value to set at row 1, column 3.
	 * \param[in] m21 The value to set at row 2, column 1.
	 * \param[in] m22 The value to set at row 2, column 2.
	 * \param[in] m23 The value to set at row 2, column 3.
	 * \param[in] m31 The value to set at row 3, column 1.
	 * \param[in] m32 The value to set at row 3, column 2.
	 * \param[in] m33 The value to set at row 3, column 3.
	 */
	NIFLIB_API Matrix33(
		float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33
	) {
		rows[0][0] = m11; rows[0][1] = m12; rows[0][2] = m13;
		rows[1][0] = m21; rows[1][1] = m22; rows[1][2] = m23;
		rows[2][0] = m31; rows[2][1] = m32; rows[2][2] = m33;
	}

	/*! This function can be used to set all values in this matrix at the same time.
	 * \param[in] m11 The value to set at row 1, column 1.
	 * \param[in] m12 The value to set at row 1, column 2.
	 * \param[in] m13 The value to set at row 1, column 3.
	 * \param[in] m21 The value to set at row 2, column 1.
	 * \param[in] m22 The value to set at row 2, column 2.
	 * \param[in] m23 The value to set at row 2, column 3.
	 * \param[in] m31 The value to set at row 3, column 1.
	 * \param[in] m32 The value to set at row 3, column 2.
	 * \param[in] m33 The value to set at row 3, column 3.
	 */
	NIFLIB_API void Set(
		float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33
	) {
		rows[0][0] = m11; rows[0][1] = m12; rows[0][2] = m13;
		rows[1][0] = m21; rows[1][1] = m22; rows[1][2] = m23;
		rows[2][0] = m31; rows[2][1] = m32; rows[2][2] = m33;
	}

	/*! Returns a quaternion representation of the rotation stored in this matrix. 
	 * \return A quaternion with an equivalent rotation to the one stored in this matrix.
	 */
	NIFLIB_API Quaternion AsQuaternion() const;

	/*! Calculates the determinant of this matrix.
	 * \return The determinant of this matrix.
	 */
	NIFLIB_API float Determinant() const;

	//Undocumented
	NIFLIB_API void AsFloatArr( float out[3][3] ) {
		out[0][0] = rows[0][0]; out[0][1] = rows[0][1]; out[0][2] = rows[0][2];
		out[1][0] = rows[1][0]; out[1][1] = rows[1][1]; out[1][2] = rows[1][2];
		out[2][0] = rows[2][0]; out[2][1] = rows[2][1]; out[2][2] = rows[2][2];
	}

   NIFLIB_API Matrix33 operator*( const Matrix33 & m ) const;
};


/* Stores four floating point numbers.  Used as a row of a Matrix44. */
struct Float4 {
	float data[4]; /*!< The four floating point numbers stored as an array. */ 

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	 * \param[in] n The index into the data array.  Should be 0, 1, 2, or 3.
	 * \return The value at the given array index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API float & operator[](int n) {
		return data[n];
	}

	/*! The bracket operator makes it possible to use this structure like a C++ array.
	 * \param[in] n The index into the data array.  Should be 0, 1, 2, or 3.
	 * \return The value at the given array index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API float operator[](int n) const {
		return data[n];
	}

	/*! Default Constructor.*/
	NIFLIB_API Float4() {}

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] f1 The value to set the first floating point number to.
	 * \param[in] f2 The value to set the second floating point number to.
	 * \param[in] f3 The value to set the third floating point number to.
	 * \param[in] f4 The value to set the fourth floating point number to.
	 */
	NIFLIB_API Float4( float f1, float f2, float f3, float f4 ) {
		data[0] = f1;
		data[1] = f2;
		data[2] = f3;
		data[3] = f4;
	}

	/*! This constructor can be used to initialize this Float4 with a Vector4
	* \param[in] v The Vector4 to construct this one from
	*/
	NIFLIB_API Float4( const Vector4 & v) { Set(v.x, v.y, v.z, v.w); }

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] f1 The value to set the first floating point number to.
	 * \param[in] f2 The value to set the second floating point number to.
	 * \param[in] f3 The value to set the third floating point number to.
	 * \param[in] f4 The value to set the fourth floating point number to.
	 */
	NIFLIB_API void Set( float f1, float f2, float f3, float f4 ) {
		data[0] = f1;
		data[1] = f2;
		data[2] = f3;
		data[3] = f4;
	}
};

/*! Stores a 4 by 4 matrix used for combined transformations. */
struct Matrix44 {
	/*! The 4x4 identity matrix constant */
	NIFLIB_API static const Matrix44 IDENTITY;

	Float4 rows[4]; /*!< The three rows of Float3 structures which hold three floating point numbers each. */ 
	
	/*! The bracket operator makes it possible to use this structure like a 4x4 C++ array.
	 * \param[in] n The index into the row array.  Should be 0, 1, 2, or 3.
	 * \return The Float4 structure for the given row index by reference so it can be read or set via the bracket operator.
	 */
	NIFLIB_API Float4 & operator[](int n) {
		return rows[n];
	}
	NIFLIB_API Float4 const & operator[](int n) const {
		return rows[n];
	}

	/*! Default constructor. Initializes Matrix to Identity. */
	NIFLIB_API Matrix44();

	/*! Copy constructor.  Initializes Matrix to another Matrix44.
	 * \param[in] m The matrix to initialize this one to. 
	 */
	NIFLIB_API Matrix44( const Matrix44 & m ) { memcpy(rows, m.rows, sizeof(Float4) * 4); }

	/*! This constructor can be used to set all values in this matrix during initialization
	 * \param[in] m11 The value to set at row 1, column 1.
	 * \param[in] m12 The value to set at row 1, column 2.
	 * \param[in] m13 The value to set at row 1, column 3.
	 * \param[in] m14 The value to set at row 1, column 4.
	 * \param[in] m21 The value to set at row 2, column 1.
	 * \param[in] m22 The value to set at row 2, column 2.
	 * \param[in] m23 The value to set at row 2, column 3.
	 * \param[in] m24 The value to set at row 2, column 4.
	 * \param[in] m31 The value to set at row 3, column 1.
	 * \param[in] m32 The value to set at row 3, column 2.
	 * \param[in] m33 The value to set at row 3, column 3.
	 * \param[in] m34 The value to set at row 3, column 4.
	 * \param[in] m41 The value to set at row 4, column 1.
	 * \param[in] m42 The value to set at row 4, column 2.
	 * \param[in] m43 The value to set at row 4, column 3.
	 * \param[in] m44 The value to set at row 4, column 4.
	 */
	NIFLIB_API Matrix44(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	) {
		rows[0][0] = m11; rows[0][1] = m12; rows[0][2] = m13; rows[0][3] = m14;
		rows[1][0] = m21; rows[1][1] = m22; rows[1][2] = m23; rows[1][3] = m24;
		rows[2][0] = m31; rows[2][1] = m32; rows[2][2] = m33; rows[2][3] = m34;
		rows[3][0] = m41; rows[3][1] = m42; rows[3][2] = m43; rows[3][3] = m44;
	}

	/*! This constructor allows a 4x4 transform matrix to be initalized from a
	 * translate vector, a 3x3 rotation matrix, and a scale factor.
	 * \param[in] translate The translation vector that specifies the new x, y, and z coordinates.
	 * \param[in] rotation The 3x3 rotation matrix.
	 * \param[in] scale The scale factor.
	 */
	NIFLIB_API Matrix44( const Vector3 & translate, const Matrix33 & rotation, float scale );

	/*! This constructor allows a 4x4 transform matrix to be initalized from a
	 * a 3x3 rotation matrix.
	 * \param[in] rotation The 3x3 rotation matrix.
	 */
	NIFLIB_API Matrix44( const Matrix33 & rotation );

	/*! This function can be used to set all values in this matrix at the same time.
	 * \param[in] m11 The value to set at row 1, column 1.
	 * \param[in] m12 The value to set at row 1, column 2.
	 * \param[in] m13 The value to set at row 1, column 3.
	 * \param[in] m14 The value to set at row 1, column 4.
	 * \param[in] m21 The value to set at row 2, column 1.
	 * \param[in] m22 The value to set at row 2, column 2.
	 * \param[in] m23 The value to set at row 2, column 3.
	 * \param[in] m24 The value to set at row 2, column 4.
	 * \param[in] m31 The value to set at row 3, column 1.
	 * \param[in] m32 The value to set at row 3, column 2.
	 * \param[in] m33 The value to set at row 3, column 3.
	 * \param[in] m34 The value to set at row 3, column 4.
	 * \param[in] m41 The value to set at row 4, column 1.
	 * \param[in] m42 The value to set at row 4, column 2.
	 * \param[in] m43 The value to set at row 4, column 3.
	 * \param[in] m44 The value to set at row 4, column 4.
	 */
	NIFLIB_API void Set(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	) {
		rows[0][0] = m11; rows[0][1] = m12; rows[0][2] = m13; rows[0][3] = m14;
		rows[1][0] = m21; rows[1][1] = m22; rows[1][2] = m23; rows[1][3] = m24;
		rows[2][0] = m31; rows[2][1] = m32; rows[2][2] = m33; rows[2][3] = m34;
		rows[3][0] = m41; rows[3][1] = m42; rows[3][2] = m43; rows[3][3] = m44;
	}

	/* Multiplies this matrix by another.
	 * \param[in] rh The matrix to multiply this one with.
	 * \return The result of the multiplication.
	 */
	NIFLIB_API Matrix44 operator*( const Matrix44 & rh ) const;

	/* Multiplies this matrix by another and sets the result to itself.
	 * \param[in] rh The matrix to multiply this one with.
	 * \return This matrix is returned.
	 */
	NIFLIB_API Matrix44 & operator*=( const Matrix44 & rh );

	/* Multiplies this matrix by a scalar value.
	 * \param[in] rh The scalar value to multiply each component of this matrix by.
	 * \return The result of the multiplication.
	 */
	NIFLIB_API Matrix44 operator*( float rh ) const;

	/* Multiplies this matrix by a scalar value and sets the resutl to itself.
	 * \param[in] rh The scalar value to multiply each component of this matrix by.
	 * \return This matrix is returned.
	 */
	NIFLIB_API Matrix44 & operator*=( float rh );

	/* Multiplies this matrix by a vector with x, y, and z components.
	 * \param[in] rh The vector to multiply this matrix with.
	 * \return The result of the multiplication.
	 */
	NIFLIB_API Vector3 operator*( const Vector3 & rh ) const;

	/* Adds this matrix to another.
	 * \param[in] rh The matrix to be added to this one.
	 * \return The result of the addition.
	 */
	NIFLIB_API Matrix44 operator+( const Matrix44 & rh ) const;

	/* Adds this matrix to another and sets the result to itself.
	 * \param[in] rh The matrix to be added to this one.
	 * \return This matrix is returned.
	 */
	NIFLIB_API Matrix44 & operator+=( const Matrix44 & rh );

	/* Adds this matrix to another.
	* \param[in] rh The matrix to be added to this one.
	* \return The result of the addition.
	*/
	NIFLIB_API Matrix44 operator-( const Matrix44 & rh ) const;

	/* Adds this matrix to another and sets the result to itself.
	* \param[in] rh The matrix to be added to this one.
	* \return This matrix is returned.
	*/
	NIFLIB_API Matrix44 & operator-=( const Matrix44 & rh );

	/* Sets the values of this matrix to those of the given matrix.
	 * \param[in] rh The matrix to copy values from.
	 * \return This matrix is returned.
	 */
	NIFLIB_API Matrix44 & operator=( const Matrix44 & rh );

	/* Allows the contents of the matrix to be printed to an ostream.
	 * \param[in] lh The ostream to insert the text into.
	 * \param[in] rh The matrix to insert into the stream.
	 * \return The given ostream is returned.
	 */
	NIFLIB_API friend ostream & operator<<( ostream & lh, const Matrix44 & rh );

	/* Compares two 4x4 matricies.  They are considered equal if all components are equal.
	 * \param[in] rh The matrix to compare this one with.
	 * \return true if the matricies are equal, false otherwise.
	 */
	NIFLIB_API bool operator==( const Matrix44 & rh ) const;

	/* Compares two 4x4 matricies.  They are considered inequal if any corresponding
	 * components are inequal.
	 * \param[in] rh The matrix to compare this one with.
	 * \return true if the matricies are inequal, false otherwise.
	 */
	NIFLIB_API bool operator!=( const Matrix44 & rh ) const;

	/*! Calculates the transpose of this matrix.
	 * \return The transpose of this matrix.
	 */
	NIFLIB_API Matrix44 Transpose() const;

	/*! Calculates the determinant of this matrix.
	 * \return The determinant of this matrix.
	 */
	NIFLIB_API float Determinant() const;

	/*! Calculates the inverse of this matrix.
	 * \return The inverse of this matrix.
	 */
	NIFLIB_API Matrix44 Inverse() const;

	/*! Returns a 3x3 submatrix of this matrix created by skipping the indicated row and column.
	 * \param[in] skip_r The row to skip.  Must be a value between 0 and 3.
	 * \param[in] skip_c The colum to skip.  Must be a value between 0 and 3.
	 * \return The 3x3 submatrix obtained by skipping the indicated row and column.
	 */
	NIFLIB_API Matrix33 Submatrix( int skip_r, int skip_c ) const;

	/*! Calculates the adjunct of this matrix created by skipping the indicated row and column.
	 * \param[in] skip_r The row to skip.  Must be a value between 0 and 3.
	 * \param[in] skip_c The colum to skip.  Must be a value between 0 and 3.
	 * \return The adjunct obtained by skipping the indicated row and column.
	 */
	NIFLIB_API float Adjoint( int skip_r, int skip_c ) const;

	NIFLIB_API Matrix33 GetRotation() const;
	NIFLIB_API float GetScale() const;
	NIFLIB_API Vector3 GetTranslation() const;

	//undocumented, may be removed
	NIFLIB_API void AsFloatArr( float out[4][4] ) {
		out[0][0] = rows[0][0]; out[0][1] = rows[0][1]; out[0][2] = rows[0][2]; out[0][3] = rows[0][3];
		out[1][0] = rows[1][0]; out[1][1] = rows[1][1]; out[1][2] = rows[1][2]; out[1][3] = rows[1][3];
		out[2][0] = rows[2][0]; out[2][1] = rows[2][1]; out[2][2] = rows[2][2]; out[2][3] = rows[2][3];
		out[3][0] = rows[3][0]; out[3][1] = rows[3][1]; out[3][2] = rows[3][2]; out[3][3] = rows[3][3];
	}

   // undocumented
   NIFLIB_API void Decompose( Vector3 & translate, Matrix33 & rotation, float & scale ) const;
};

/*! Stores a color along with alpha translucency */
struct Color3 {
	float r; /*!< The red component of this color.  Should be between 0.0f and 1.0f. */ 
	float g; /*!< The green component of this color.  Should be between 0.0f and 1.0f. */ 
	float b; /*!< The blue component of this color.  Should be between 0.0f and 1.0f. */ 

	/*! Default constructor */
	NIFLIB_API Color3() {}

	/*! Copy constructor */
	NIFLIB_API Color3(const Color3& src) {
		this->r = src.r;
		this->g = src.g;
		this->b = src.b;
	}

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] r The value to set the red component of this color to.  Should be between 0.0f and 1.0f.
	 * \param[in] g The value to set the green component of this color to. Should be between 0.0f and 1.0f.
	 * \param[in] b The value to set the blue component of this color to.  Should be between 0.0f and 1.0f.
	 */
	NIFLIB_API Color3(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] r The value to set the red component of this color to.  Should be between 0.0f and 1.0f.
	 * \param[in] g The value to set the green component of this color to. Should be between 0.0f and 1.0f.
	 * \param[in] b The value to set the blue component of this color to.  Should be between 0.0f and 1.0f.
	 */
	NIFLIB_API void Set(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

/*! Stores a color along with alpha translucency */
struct Color4 {
	float r; /*!< The red component of this color.  Should be between 0.0f and 1.0f. */ 
	float g; /*!< The green component of this color.  Should be between 0.0f and 1.0f. */ 
	float b; /*!< The blue component of this color.  Should be between 0.0f and 1.0f. */ 
	float a; /*!< The alpha translucency component of this color.  Should be between 0.0f and 1.0f. */ 

	NIFLIB_API Color4 operator+(const Color4& rhs) const
	{
		Color4 ret;
		ret = *this;
		ret.r += rhs.r;
		ret.g += rhs.g;
		ret.b += rhs.b;
		ret.a += rhs.a;
		return ret;
	}

	NIFLIB_API Color4 operator-(const Color4& rhs) const
	{
		Color4 ret;
		ret = *this;
		ret.r -= rhs.r;
		ret.g -= rhs.g;
		ret.b -= rhs.b;
		ret.a -= rhs.a;
		return ret;
	}

	NIFLIB_API Color4 operator+(const float rhs) const
	{
		Color4 ret;
		ret = *this;
		ret.r += rhs;
		ret.g += rhs;
		ret.b += rhs;
		ret.a += rhs;
		return ret;
	}

	NIFLIB_API Color4 operator-(const float rhs) const
	{
		Color4 ret;
		ret = *this;
		ret.r -= rhs;
		ret.g -= rhs;
		ret.b -= rhs;
		ret.a -= rhs;
		return ret;
	}

	NIFLIB_API Color4 operator*(const float rhs) const
	{
		Color4 ret;
		ret = *this;
		ret.r *= rhs;
		ret.g *= rhs;
		ret.b *= rhs;
		ret.a *= rhs;
		return ret;
	}

	NIFLIB_API Color4 operator/(const float rhs) const
	{
		Color4 ret;
		ret = *this;
		ret.r /= rhs;
		ret.g /= rhs;
		ret.b /= rhs;
		ret.a /= rhs;
		return ret;
	}

	/*! Default constructor */
	NIFLIB_API Color4() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}

	/*! Copy constructor */
	NIFLIB_API Color4(const Color4& src) : r(src.r), g(src.g), b(src.b), a(src.a) {}

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] r The value to set the red component of this color to.  Should be between 0.0f and 1.0f.
	 * \param[in] g The value to set the green component of this color to. Should be between 0.0f and 1.0f.
	 * \param[in] b The value to set the blue component of this color to.  Should be between 0.0f and 1.0f.
	 * \param[in] a The value to set the alpha translucency component of this color to.  Should be between 0.0f and 1.0f.
	 */
	NIFLIB_API Color4(float r, float g, float b, float a = 1.0f) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] r The value to set the red component of this color to.  Should be between 0.0f and 1.0f.
	 * \param[in] g The value to set the green component of this color to. Should be between 0.0f and 1.0f.
	 * \param[in] b The value to set the blue component of this color to.  Should be between 0.0f and 1.0f.
	 * \param[in] a The value to set the alpha translucency component of this color to.  Should be between 0.0f and 1.0f.
	 */
	NIFLIB_API void Set(float r, float g, float b, float a = 1.0f) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	NIFLIB_API bool operator==( const Color4 & n ) const {
		return ( r == n.r && g == n.g && b == n.b && a == n.a );
	}

	NIFLIB_API bool operator!=( const Color4 & n ) const {
		return ( r != n.r || g != n.g || b != n.b || a != n.a );
	}
};

/*! Represents a quaternion - a 4D extention of complex numbers used as an alternitive to matrices to represent rotation.*/
struct Quaternion {
	float w; /*!< The W scalar component of this Quaternion. */ 
	float x; /*!< The X vector component of this Quaternion. */ 
	float y; /*!< The Y vector component of this Quaternion. */ 
	float z; /*!< The Z vector component of this Quaternion. */ 

	/*! Default constructor. */
	NIFLIB_API Quaternion() {}

	/*! This constructor can be used to set all values in this structure during initialization
	 * \param[in] w The value to set the W scalar component of this quaternion to.
	 * \param[in] x The value to set the X vector component of this quaternion to.
	 * \param[in] y The value to set the Y vector component of this quaternion to.
	 * \param[in] z The value to set the Z vector component of this quaternion to.
	 */
	NIFLIB_API Quaternion(float w, float x, float y, float z) {
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/* Dot-product */
	NIFLIB_API float Dot(const Quaternion &rhs) const {
		return  x * rhs.x + 
			y * rhs.y + 
			z * rhs.z + 
			w * rhs.w;
	}

	/* Multiplication */
	NIFLIB_API Quaternion operator*(const float &rhs) const {
		Quaternion ret;
		ret = *this;
		ret.x *= rhs;
		ret.y *= rhs;
		ret.z *= rhs;
		ret.w *= rhs;
		return ret;
	}

	/* Addition */
	NIFLIB_API Quaternion operator+(const Quaternion &rhs) const {
		Quaternion ret;
		ret = *this;
		ret.x += rhs.x;
		ret.y += rhs.y;
		ret.z += rhs.z;
		ret.w += rhs.w;
		return ret;
	}

	/* Equality */
	NIFLIB_API bool operator==( const Quaternion & n ) const {
		return ( x == n.x && y == n.y && z == n.z && w == n.w );
	}

	/*! This function can be used to set all values in the structure at the same time.
	 * \param[in] w The value to set the W scalar component of this quaternion to.
	 * \param[in] x The value to set the X vector component of this quaternion to.
	 * \param[in] y The value to set the Y vector component of this quaternion to.
	 * \param[in] z The value to set the Z vector component of this quaternion to.
	 */
	NIFLIB_API void Set(float w, float x, float y, float z) {
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/*! This function returns a 3x3 matrix representation of the rotation stored in this quaternion.
	 * \return a Matrix33 structure with an equivalent rotation to this quaternion.
	 */
	NIFLIB_API Matrix33 AsMatrix();

	/*! This function returns a Euler Angle representation of the rotation stored in this quaternion.
	 * The angles returned correspond to yaw, pitch, and roll and are in radiens.
	 * \return a Float3 structure with the first value containing the yaw, the second the pitch,
	 * and the third the roll.  The values are in radians.
	 */
	NIFLIB_API Float3 AsEulerYawPitchRoll();

	/*! Calculates the inverse of this quaternion.
	* \return The inverse of this quaternion.
	*/
	NIFLIB_API Quaternion Inverse() const;
};


/*! Stores a 4 by 3 matrix used for tensors. */
struct InertiaMatrix {
	/*! The 4x3 identity matrix constant */
	NIFLIB_API static const InertiaMatrix IDENTITY;

	Float4 rows[3]; /*!< The three rows of Float3 structures which hold three floating point numbers each. */ 

	/*! The bracket operator makes it possible to use this structure like a 4x4 C++ array.
	* \param[in] n The index into the row array.  Should be 0, 1, 2, or 3.
	* \return The Float4 structure for the given row index by reference so it can be read or set via the bracket operator.
	*/
	NIFLIB_API Float4 & operator[](int n) {
		return rows[n];
	}
	NIFLIB_API Float4 const & operator[](int n) const {
		return rows[n];
	}

	/*! Default constructor. Initializes Matrix to Identity. */
	NIFLIB_API InertiaMatrix();

	/*! Copy constructor.  Initializes Matrix to another InertiaMatrix.
	* \param[in] m The matrix to initialize this one to. 
	*/
	NIFLIB_API InertiaMatrix( const InertiaMatrix & m ) { memcpy(rows, m.rows, sizeof(Float4) * _countof(rows)); }

	/*! This constructor can be used to set all values in this matrix during initialization
	* \param[in] m11 The value to set at row 1, column 1.
	* \param[in] m12 The value to set at row 1, column 2.
	* \param[in] m13 The value to set at row 1, column 3.
	* \param[in] m14 The value to set at row 1, column 4.
	* \param[in] m21 The value to set at row 2, column 1.
	* \param[in] m22 The value to set at row 2, column 2.
	* \param[in] m23 The value to set at row 2, column 3.
	* \param[in] m24 The value to set at row 2, column 4.
	* \param[in] m31 The value to set at row 3, column 1.
	* \param[in] m32 The value to set at row 3, column 2.
	* \param[in] m33 The value to set at row 3, column 3.
	* \param[in] m34 The value to set at row 3, column 4.
	* \param[in] m41 The value to set at row 4, column 1.
	* \param[in] m42 The value to set at row 4, column 2.
	* \param[in] m43 The value to set at row 4, column 3.
	* \param[in] m44 The value to set at row 4, column 4.
	*/
	NIFLIB_API InertiaMatrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34
		) {
			rows[0][0] = m11; rows[0][1] = m12; rows[0][2] = m13; rows[0][3] = m14;
			rows[1][0] = m21; rows[1][1] = m22; rows[1][2] = m23; rows[1][3] = m24;
			rows[2][0] = m31; rows[2][1] = m32; rows[2][2] = m33; rows[2][3] = m34;
	}

	/*! This constructor allows a 4x4 transform matrix to be initalized from a
	* a 3x3 rotation matrix.
	* \param[in] rotation The 3x3 rotation matrix.
	*/
	NIFLIB_API InertiaMatrix( const Matrix33 & rotation );

	/*! This function can be used to set all values in this matrix at the same time.
	* \param[in] m11 The value to set at row 1, column 1.
	* \param[in] m12 The value to set at row 1, column 2.
	* \param[in] m13 The value to set at row 1, column 3.
	* \param[in] m14 The value to set at row 1, column 4.
	* \param[in] m21 The value to set at row 2, column 1.
	* \param[in] m22 The value to set at row 2, column 2.
	* \param[in] m23 The value to set at row 2, column 3.
	* \param[in] m24 The value to set at row 2, column 4.
	* \param[in] m31 The value to set at row 3, column 1.
	* \param[in] m32 The value to set at row 3, column 2.
	* \param[in] m33 The value to set at row 3, column 3.
	* \param[in] m34 The value to set at row 3, column 4.
	*/
	NIFLIB_API void Set(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34
		) {
			rows[0][0] = m11; rows[0][1] = m12; rows[0][2] = m13; rows[0][3] = m14;
			rows[1][0] = m21; rows[1][1] = m22; rows[1][2] = m23; rows[1][3] = m24;
			rows[2][0] = m31; rows[2][1] = m32; rows[2][2] = m33; rows[2][3] = m34;
	}

	/* Multiplies this matrix by another.
	* \param[in] rh The matrix to multiply this one with.
	* \return The result of the multiplication.
	*/
	NIFLIB_API InertiaMatrix operator*( const InertiaMatrix & rh ) const;

	/* Multiplies this matrix by another and sets the result to itself.
	* \param[in] rh The matrix to multiply this one with.
	* \return This matrix is returned.
	*/
	NIFLIB_API InertiaMatrix & operator*=( const InertiaMatrix & rh );

	/* Multiplies this matrix by a scalar value.
	* \param[in] rh The scalar value to multiply each component of this matrix by.
	* \return The result of the multiplication.
	*/
	NIFLIB_API InertiaMatrix operator*( float rh ) const;

	/* Multiplies this matrix by a scalar value and sets the resutl to itself.
	* \param[in] rh The scalar value to multiply each component of this matrix by.
	* \return This matrix is returned.
	*/
	NIFLIB_API InertiaMatrix & operator*=( float rh );

	/* Multiplies this matrix by a vector with x, y, and z components.
	* \param[in] rh The vector to multiply this matrix with.
	* \return The result of the multiplication.
	*/
	NIFLIB_API Vector3 operator*( const Vector3 & rh ) const;

	/* Adds this matrix to another.
	* \param[in] rh The matrix to be added to this one.
	* \return The result of the addition.
	*/
	NIFLIB_API InertiaMatrix operator+( const InertiaMatrix & rh ) const;

	/* Adds this matrix to another and sets the result to itself.
	* \param[in] rh The matrix to be added to this one.
	* \return This matrix is returned.
	*/
	NIFLIB_API InertiaMatrix & operator+=( const InertiaMatrix & rh );

	/* Sets the values of this matrix to those of the given matrix.
	* \param[in] rh The matrix to copy values from.
	* \return This matrix is returned.
	*/
	NIFLIB_API InertiaMatrix & operator=( const InertiaMatrix & rh );

	/* Allows the contents of the matrix to be printed to an ostream.
	* \param[in] lh The ostream to insert the text into.
	* \param[in] rh The matrix to insert into the stream.
	* \return The given ostream is returned.
	*/
	NIFLIB_API friend ostream & operator<<( ostream & lh, const InertiaMatrix & rh );

	/* Compares two 4x4 matricies.  They are considered equal if all components are equal.
	* \param[in] rh The matrix to compare this one with.
	* \return true if the matricies are equal, false otherwise.
	*/
	NIFLIB_API bool operator==( const InertiaMatrix & rh ) const;

	/* Compares two 4x4 matricies.  They are considered inequal if any corresponding
	* components are inequal.
	* \param[in] rh The matrix to compare this one with.
	* \return true if the matricies are inequal, false otherwise.
	*/
	NIFLIB_API bool operator!=( const InertiaMatrix & rh ) const;

	/*! Calculates the transpose of this matrix.
	* \return The transpose of this matrix.
	*/
	NIFLIB_API InertiaMatrix Transpose() const;

	/*! Calculates the determinant of this matrix.
	* \return The determinant of this matrix.
	*/
	NIFLIB_API float Determinant() const;

	/*! Calculates the inverse of this matrix.
	* \return The inverse of this matrix.
	*/
	NIFLIB_API InertiaMatrix Inverse() const;

	/*! Returns a 3x3 submatrix of this matrix created by skipping the indicated row and column.
	* \param[in] skip_r The row to skip.  Must be a value between 0 and 3.
	* \param[in] skip_c The colum to skip.  Must be a value between 0 and 3.
	* \return The 3x3 submatrix obtained by skipping the indicated row and column.
	*/
	NIFLIB_API Matrix33 Submatrix( int skip_r, int skip_c ) const;

	/*! Calculates the adjunct of this matrix created by skipping the indicated row and column.
	* \param[in] skip_r The row to skip.  Must be a value between 0 and 3.
	* \param[in] skip_c The colum to skip.  Must be a value between 0 and 3.
	* \return The adjunct obtained by skipping the indicated row and column.
	*/
	NIFLIB_API float Adjoint( int skip_r, int skip_c ) const;
};


//--ostream functions for printing with cout--//

NIFLIB_API ostream & operator<<( ostream & out, TexCoord const & val );
NIFLIB_API ostream & operator<<( ostream & out, Triangle const & val );
NIFLIB_API ostream & operator<<( ostream & out, Vector3 const & val );
NIFLIB_API ostream & operator<<( ostream & out, Float2 const & val );
NIFLIB_API ostream & operator<<( ostream & out, Matrix22 const & val );
NIFLIB_API ostream & operator<<( ostream & out, Float3 const & val );
NIFLIB_API ostream & operator<<( ostream & out, Matrix33 const & val );
NIFLIB_API ostream & operator<<( ostream & out, Float4 const & val );
NIFLIB_API ostream & operator<<( ostream & out, Color3 const & val );
NIFLIB_API ostream & operator<<( ostream & out, Color4 const & val );
NIFLIB_API ostream & operator<<( ostream & out, Quaternion const & val );
NIFLIB_API ostream & operator<<( ostream & out, Matrix44 const & val );
NIFLIB_API ostream & operator<<( ostream & out, InertiaMatrix const & val );

}
#endif
