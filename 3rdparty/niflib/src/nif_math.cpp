/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#include "../include/nif_math.h"
#include <iomanip>
using namespace Niflib;

//Constants

const Matrix44 Matrix44::IDENTITY( 1.0f, 0.0f, 0.0f, 0.0f,
								   0.0f, 1.0f, 0.0f, 0.0f,
								   0.0f, 0.0f, 1.0f, 0.0f,
								   0.0f, 0.0f, 0.0f, 1.0f );

const Matrix33 Matrix33::IDENTITY( 1.0f, 0.0f, 0.0f,
								   0.0f, 1.0f, 0.0f,
								   0.0f, 0.0f, 1.0f );

const Matrix22 Matrix22::IDENTITY( 1.0f, 0.0f,
								   0.0f, 1.0f );

const InertiaMatrix InertiaMatrix::IDENTITY( 
								  1.0f, 0.0f, 0.0f, 0.0f,
								  0.0f, 1.0f, 0.0f, 0.0f,
								  0.0f, 0.0f, 1.0f, 0.0f );

/* TexCoord Methods
 *
 */

bool TexCoord::operator==( const TexCoord & n ) const {
	return ( u == n.u && v == n.v );
}


/*
 * Vector3 Methods
 */

float Vector3::Magnitude() const {
	return sqrt( x * x + y * y + z * z );
}

Vector3 Vector3::Normalized() const {
	Vector3 v(*this);
	float m = Magnitude();
	return Vector3(
		x / m, //x
		y / m, //y
		z / m //z
	);
}

Vector3 Vector3::operator+( const Vector3 & rh) const {
	Vector3 v(*this);
	v += rh;
	return v;
}

Vector3 Vector3::operator+( const float & rh) const {
	Vector3 v(*this);
	v += rh;
	return v;
}

Vector3 & Vector3::operator+=( const Vector3 & rh ) {
	x += rh.x;
	y += rh.y;
	z += rh.z;

	return *this;
}

Vector3 & Vector3::operator+=( const float & rh ) {
	x += rh;
	y += rh;
	z += rh;

	return *this;
}

Vector3 Vector3::operator-( const Vector3 & rh) const {
	Vector3 v(*this);
	v -= rh;
	return v;
}

Vector3 Vector3::operator-( const float & rh) const {
	Vector3 v(*this);
	v -= rh;
	return v;
}

Vector3 & Vector3::operator-=( const Vector3 & rh ) {
	x -= rh.x;
	y -= rh.y;
	z -= rh.z;

	return *this;
}

Vector3 & Vector3::operator-=( const float & rh ) {
	x -= rh;
	y -= rh;
	z -= rh;

	return *this;
}

Vector3 Vector3::operator*( const float & rh) const {
	Vector3 v(*this);
	v *= rh;
	return v;
}

Vector3 & Vector3::operator*=( const float & rh) {
	x *= rh;
	y *= rh;
	z *= rh;

	return *this;
}

float Vector3::operator*( const Vector3 & v ) const {
	return DotProduct(v);
}

Vector3 Vector3::operator^( const Vector3 & v ) const {
	return CrossProduct(v);
}

Vector3 Vector3::operator/( const float & rh ) const {
	Vector3 v(*this);
	v /= rh;
	return v;
}

Vector3 & Vector3::operator/=( const float & rh ) {
	x /= rh;
	y /= rh;
	z /= rh;

	return *this;
}

bool Vector3::operator==( const Vector3 & rh) const {
	if (rh.x == x && rh.y == y && rh.z == z)
		return true;
	else
		return false;
}

bool Vector3::operator!=( const Vector3 & rh) const {
	if (rh.x == x && rh.y == y && rh.z == z)
		return false;
	else
		return true;
}

float & Vector3::operator[](int n) {
	switch (n) {
			case 0: return x; break;
			case 1: return y; break;
			case 2: return z; break;
			default: throw std::out_of_range("Index out of range for Vector3");
	};
}

float Vector3::operator[](int n) const {
	switch (n) {
			case 0: return x; break;
			case 1: return y; break;
			case 2: return z; break;
			default: throw std::out_of_range("Index out of range for Vector3");
	};
}

float Vector3::DotProduct( const Vector3 & rh) const {
	return x * rh.x + y * rh.y + z * rh.z;
}

Vector3 Vector3::CrossProduct( const Vector3 & rh) const {
	return Vector3(
		y * rh.z - z * rh.y, //x
		z * rh.x - x * rh.z, //y
		x * rh.y - y * rh.x //z
	);
}

//Vector3 Vector3::operator*( const Matrix44 & rh) const {
//	return rh * (*this);
//}
//
//Vector & Vector3::operator*=( const Matrix44 & rh) {
//	*this = rh * (*this);
//	return *this;
//}


/*
* Vector4 Methods
*/
Vector4::Vector4( const Float4 & v) { 
	x = v[0]; y = v[1]; z = v[2]; w = v[3];
}

float Vector4::Magnitude() const {
	return sqrt( x * x + y * y + z * z + w * w );
}

Vector4 Vector4::Normalized() const {
	Vector4 v(*this);
	float m = Magnitude();
	return Vector4(
		x / m, //x
		y / m, //y
		z / m, //z
		w / m
		);
}

Vector4 Vector4::operator+( const Vector4 & rh) const {
	Vector4 v(*this);
	v += rh;
	return v;
}

Vector4 & Vector4::operator+=( const Vector4 & rh ) {
	x += rh.x;
	y += rh.y;
	z += rh.z;
	w += rh.w;
	return *this;
}

Vector4 Vector4::operator-( const Vector4 & rh) const {
	Vector4 v(*this);
	v -= rh;
	return v;
}

Vector4 & Vector4::operator-=( const Vector4 & rh ) {
	x -= rh.x;
	y -= rh.y;
	z -= rh.z;
	w -= rh.w;
	return *this;
}

Vector4 Vector4::operator*( const float & rh) const {
	Vector4 v(*this);
	v *= rh;
	return v;
}

Vector4 & Vector4::operator*=( const float & rh) {
	x *= rh;
	y *= rh;
	z *= rh;
	w *= rh;
	return *this;
}

Vector4 Vector4::operator/( const float & rh ) const {
	Vector4 v(*this);
	v /= rh;
	return v;
}

Vector4 & Vector4::operator/=( const float & rh ) {
	x /= rh;
	y /= rh;
	z /= rh;
	w /= rh;
	return *this;
}

bool Vector4::operator==( const Vector4 & rh) const {
	if (rh.x == x && rh.y == y && rh.z == z && rh.w == w)
		return true;
	else
		return false;
}

bool Vector4::operator!=( const Vector4 & rh) const {
	if (rh.x == x && rh.y == y && rh.z == z && rh.w == w)
		return false;
	else
		return true;
}

float & Vector4::operator[](int n) {
	switch (n) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw runtime_error("Invalid index");
	}
}

float Vector4::operator[](int n) const {
	switch (n) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: throw runtime_error("Invalid index");
	}
}


/*
 * Matrix22 Methods
 */

Matrix22::Matrix22() {
	*this = Matrix22::IDENTITY;
}

/*
 * Matrix33 Methods
 */

Matrix33::Matrix33() {
	*this = Matrix33::IDENTITY;
}

Matrix33::Matrix33(const Matrix33& src) {
	*this = src;
}

Quaternion Matrix33::AsQuaternion() const {
	Quaternion quat;
	float tr, s, q[4];
	int i, j, k;

	int nxt[3] = {1, 2, 0};

	const Matrix33 & m = *this;

	// compute the trace of the matrix
	tr = m[0][0] + m[1][1] + m[2][2];

	// check if the trace is positive or negative
	if (tr > 0.0) {
		s = sqrt (tr + 1.0f);
		quat.w = s / 2.0f;
		s = 0.5f / s;
		quat.x = (m[1][2] - m[2][1]) * s;
		quat.y = (m[2][0] - m[0][2]) * s;
		quat.z = (m[0][1] - m[1][0]) * s;
	}
	else {
		// trace is negative
		i = 0;
		if ( m[1][1] > m[0][0])
			i = 1;
		if ( m[2][2] > m[i][i] )
			i = 2;
		j = nxt[i];
		k = nxt[j];

		s = sqrt( ( m[i][i] - (m[j][j] + m[k][k]) ) + 1.0f );
		q[i] = s * 0.5f;
		if (s != 0.0f) s = 0.5f / s;
		q[3] = (m[j][k] - m[k][j]) * s;
		q[j] = (m[i][j] + m[j][i]) * s;
		q[k] = (m[i][k] + m[k][i]) * s;
		quat.x = q[0];
		quat.y= q[1];
		quat.z = q[2];
		quat.w = q[3];
	}

	return quat;
}

float Matrix33::Determinant() const {
	return  (*this)[0][0] * ( (*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1] )
		  - (*this)[0][1] * ( (*this)[1][0] * (*this)[2][2] - (*this)[1][2] * (*this)[2][0] )
		  + (*this)[0][2] * ( (*this)[1][0] * (*this)[2][1] - (*this)[1][1] * (*this)[2][0] );
}

Matrix33 Matrix33::operator*( const Matrix33 & m ) const
{
   Matrix33 m3;
   for ( int r = 0; r < 3; r++ ){
      for ( int c = 0; c < 3; c++ ){
         m3[r][c] = (*this)[r][0]*m[0][c] + (*this)[r][1]*m[1][c] + (*this)[r][2]*m[2][c];
      }
   }
   return m3;
}

/*
 * Matrix44 Methods
 */

Matrix44::Matrix44() {
	*this = Matrix44::IDENTITY;
}

Matrix44::Matrix44( const Matrix33 & r ) {
	//Set this matrix with rotate and translate information
	Matrix44 & m = *this;
	m[0][0] = r[0][0];  m[0][1] = r[0][1];  m[0][2] = r[0][2];  m[0][3] = 0.0f;
	m[1][0] = r[1][0];  m[1][1] = r[1][1];  m[1][2] = r[1][2];  m[1][3] = 0.0f;
	m[2][0] = r[2][0];  m[2][1] = r[2][1];  m[2][2] = r[2][2];  m[2][3] = 0.0f;
	m[3][0] = 0.0f;     m[3][1] = 0.0f;     m[3][2] = 0.0f;     m[3][3] = 1.0f;
}

Matrix44::Matrix44( const Vector3 & t, const Matrix33 & r, float scale ) {
	//Set up a matrix with rotate and translate information
	Matrix44 rt;
	rt[0][0] = r[0][0];	rt[0][1] = r[0][1];	rt[0][2] = r[0][2];	rt[0][3] = 0.0f;
	rt[1][0] = r[1][0];	rt[1][1] = r[1][1];	rt[1][2] = r[1][2];	rt[1][3] = 0.0f;
	rt[2][0] = r[2][0];	rt[2][1] = r[2][1];	rt[2][2] = r[2][2];	rt[2][3] = 0.0f;
	rt[3][0] = t.x;     rt[3][1] = t.y;     rt[3][2] = t.z;     rt[3][3] = 1.0f;

	//Set up another matrix with the scale information
	Matrix44 s;
	s[0][0] = scale;	s[0][1] = 0.0f;		s[0][2] = 0.0f;		s[0][3] = 0.0f;
	s[1][0] = 0.0f;		s[1][1] = scale;	s[1][2] = 0.0f;		s[1][3] = 0.0f;
	s[2][0] = 0.0f;		s[2][1] = 0.0f;		s[2][2] = scale;	s[2][3] = 0.0f;
	s[3][0] = 0.0f;		s[3][1] = 0.0f;		s[3][2] = 0.0f;		s[3][3] = 1.0f;

	//Multiply the two for the combined transform
	*this = s * rt;
}

Matrix33 Matrix44::GetRotation() const {
	const Matrix44 & t = *this;

	Matrix33 m( t[0][0], t[0][1], t[0][2],
	            t[1][0], t[1][1], t[1][2],
				t[2][0], t[2][1], t[2][2]
			   );

   	//--Extract Scale from first 3 rows--//
	float scale[3];
	for (int r = 0; r < 3; ++r) {
		//Get scale for this row
		scale[r] = Vector3( m[r][0], m[r][1], m[r][2] ).Magnitude();

		//Normalize the row by dividing each factor by scale
		m[r][0] /= scale[r];
		m[r][1] /= scale[r];
		m[r][2] /= scale[r];
	}

	//Return result
	return m;
}

float Matrix44::GetScale() const {
	const Matrix44 & m = *this;
	float scale[3];
	for (int r = 0; r < 3; ++r) {
		//Get scale for this row
		scale[r] = Vector3( m[r][0], m[r][1], m[r][2] ).Magnitude();
	}
	 
	//averate the scale since NIF doesn't support discreet scaling
	return (scale[0] + scale[1] + scale[2]) / 3.0f;
}


Vector3 Matrix44::GetTranslation() const {
	const Matrix44 & m = *this;
	return Vector3( m[3][0], m[3][1], m[3][2] );
}

Matrix44 Matrix44::operator*( const Matrix44 & rh ) const {
	return Matrix44(*this) *= rh;
}
Matrix44 & Matrix44::operator*=( const Matrix44 & rh ) {
	Matrix44 r;
	Matrix44 & lh = *this;
	float t;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			t = 0.0f;
			for (int k = 0; k < 4; k++) {
				t += lh[i][k] * rh[k][j];
			}
			r[i][j] = t;
		}
	}

	*this = r;
	return *this;
}

Matrix44 Matrix44::operator*( float rh ) const {
	return Matrix44(*this) *= rh;
}

Matrix44 & Matrix44::operator*=( float rh ) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			(*this)[i][j] *= rh;
		}
	}
	return *this;
}

Vector3 Matrix44::operator*( const Vector3 & rh ) const {
	const Matrix44 & t = *this;
	Vector3 v;
	//Multiply, ignoring w
	v.x = rh.x * t[0][0] + rh.y * t[1][0] + rh.z * t[2][0] + t[3][0];
	v.y = rh.x * t[0][1] + rh.y * t[1][1] + rh.z * t[2][1] + t[3][1];
	v.z = rh.x * t[0][2] + rh.y * t[1][2] + rh.z * t[2][2] + t[3][2];
	//answer[3] = rh[0] * t(0,3) + rh[1] * t(1,3) + rh[2] * t(2,3) + t(3,3);

	return v;
}

Matrix44 Matrix44::operator+( const Matrix44 & rh ) const {
	return Matrix44(*this) += rh;
} 

Matrix44 & Matrix44::operator+=( const Matrix44 & rh ) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			(*this)[i][j] += rh[i][j];
		}
	}
	return *this;
}

Matrix44 Matrix44::operator-( const Matrix44 & rh ) const {
	return Matrix44(*this) -= rh;
} 

Matrix44 & Matrix44::operator-=( const Matrix44 & rh ) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			(*this)[i][j] -= rh[i][j];
		}
	}
	return *this;
}

Matrix44 & Matrix44::operator=( const Matrix44 & rh ) {
	memcpy(rows, rh.rows, sizeof(Float4) * 4);
	return *this;
}

bool Matrix44::operator==( const Matrix44 & rh ) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ( (*this)[i][j] != rh[i][j] )
				return false;
		}
	}
	return true;
}

bool Matrix44::operator!=( const Matrix44 & rh ) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ( (*this)[i][j] != rh[i][j] )
				return true;
		}
	}
	return false;
}

Matrix44 Matrix44::Transpose() const {
	const Matrix44 & t = *this;
	return Matrix44( t[0][0], t[1][0], t[2][0], t[3][0],
					 t[0][1], t[1][1], t[2][1], t[3][1],
					 t[0][2], t[1][2], t[2][2], t[3][2],
					 t[0][3], t[1][3], t[2][3], t[3][3] );
}

Matrix33 Matrix44::Submatrix( int skip_r, int skip_c ) const {
	Matrix33 sub;
	int i = 0, j = 0;
	for (int r = 0; r < 4; r++) {
		if (r == skip_r)
			continue;
		for (int c = 0; c < 4; c++) {
			if (c == skip_c)
				continue;
			sub[i][j] = (*this)[r][c];
			j++;
		}
		i++;
		j = 0;
	}
	return sub;
}

float Matrix44::Adjoint( int skip_r, int skip_c ) const {
	Matrix33 sub = Submatrix( skip_r, skip_c );
	return pow(-1.0f, float(skip_r + skip_c)) * sub.Determinant();
}

Matrix44 Matrix44::Inverse() const {
	Matrix44 result;

	float det = Determinant();
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			result[c][r] = Adjoint(r, c) / det;
		}
	}

	return result;
}

float Matrix44::Determinant() const {
	const Matrix44 & t = *this;
	return  t[0][0] * Submatrix(0, 0).Determinant()
	      - t[0][1] * Submatrix(0, 1).Determinant()
	      + t[0][2] * Submatrix(0, 2).Determinant()
	      - t[0][3] * Submatrix(0, 3).Determinant();
}

void Matrix44::Decompose( Vector3 & translate, Matrix33 & rotation, float & scale ) const {
   translate = Vector3( (*this)[3][0], (*this)[3][1], (*this)[3][2] );
   Matrix33 rotT;
   for ( int i = 0; i < 3; i++ ){
      for ( int j = 0; j < 3; j++ ){
         rotation[i][j] = (*this)[i][j];
         rotT[j][i] = (*this)[i][j];
      }
   }
   Matrix33 mtx = rotation * rotT;
   Float3 scale3( sqrt(mtx[0][0]), sqrt(mtx[1][1]), sqrt(mtx[2][2]) );
   for ( int i = 0; i < 3; i++ ){
      for ( int j = 0; j < 3; j++ ){
         rotation[i][j] /= scale3[i];
      }
   }

   //averate the scale since NIF doesn't support discreet scaling
   scale = (scale3[0] + scale3[1] + scale3[2]) / 3.0f;
}
/*
 * Quaternion Methods
 */

Float3 Quaternion::AsEulerYawPitchRoll() {
	float yaw, pitch, roll;

	if ( x*y + z*w == 0.5 ) {
		//North Pole
		yaw = 2 * atan2(x,w);
		pitch = asin(2*x*y + 2*z*w);
		roll = 0.0f;
	}
	else if ( x*y + z*w == -0.5 ) {
		//South Pole
		yaw =  -2 * atan2(x,w);
		pitch = asin(2*x*y + 2*z*w);
		roll = 0.0f;
	}
	else {
		yaw = atan2(2*y*w-2*x*z , 1 - 2*y*y - 2*z*z);
		pitch = asin(2*x*y + 2*z*w);
		roll = atan2(2*x*w-2*y*z , 1 - 2*x*x - 2*z*z);
	}

	return Float3( yaw, pitch, roll );
}

Matrix33 Quaternion::AsMatrix() {
	Matrix33 m;

	float w2 = w * w;
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;

	m[0][0] = w2 + x2- y2 - z2;
	m[0][1] = 2.0f*x*y - 2.0f*w*z;
	m[0][2] = 2.0f*x*z + 2.0f*w*y;
	
	m[1][0] = 2.0f*x*y + 2.0f*w*z;
	m[1][1] = w2 - x2 + y*y - z2;
	m[1][2] = 2.0f*y*z - 2.0f*w*x;
	
	m[2][0] = 2.0f*x*z - 2.0f*w*y;
	m[2][1] = 2.0f*y*z + 2.0f*w*x;
	m[2][2] = w2 - x2 - y2 + z2;

	return m;
}

Quaternion Quaternion::Inverse() const {
	return Quaternion(w, -x, -y, -z);
}


/*
* InertiaMatrix Methods
*/

InertiaMatrix::InertiaMatrix() {
	*this = InertiaMatrix::IDENTITY;
}

InertiaMatrix::InertiaMatrix( const Matrix33 & r ) {
	//Set this matrix with rotate and translate information
	InertiaMatrix & m = *this;
	m[0][0] = r[0][0];  m[0][1] = r[0][1];  m[0][2] = r[0][2];  m[0][3] = 0.0f;
	m[1][0] = r[1][0];  m[1][1] = r[1][1];  m[1][2] = r[1][2];  m[1][3] = 0.0f;
	m[2][0] = r[2][0];  m[2][1] = r[2][1];  m[2][2] = r[2][2];  m[2][3] = 0.0f;
}

InertiaMatrix InertiaMatrix::operator*( const InertiaMatrix & rh ) const {
	return InertiaMatrix(*this) *= rh;
}

InertiaMatrix & InertiaMatrix::operator*=( const InertiaMatrix & rh ) {
	InertiaMatrix r;
	InertiaMatrix & lh = *this;
	float t;
	for (int i = 0; i < _countof(rows); i++) {
		for (int j = 0; j < 4; j++) {
			t = 0.0f;
			for (int k = 0; k < _countof(rows); k++) {
				t += lh[i][k] * rh[k][j];
			}
			r[i][j] = t;
		}
	}

	*this = r;
	return *this;
}

InertiaMatrix InertiaMatrix::operator*( float rh ) const {
	return InertiaMatrix(*this) *= rh;
}

InertiaMatrix & InertiaMatrix::operator*=( float rh ) {
	for (int i = 0; i < _countof(rows); i++) {
		for (int j = 0; j < 4; j++) {
			(*this)[i][j] *= rh;
		}
	}
	return *this;
}

Vector3 InertiaMatrix::operator*( const Vector3 & rh ) const {
	const InertiaMatrix & t = *this;
	Vector3 v;
	//Multiply, ignoring w
	v.x = rh.x * t[0][0] + rh.y * t[1][0] + rh.z * t[2][0];
	v.y = rh.x * t[0][1] + rh.y * t[1][1] + rh.z * t[2][1];
	v.z = rh.x * t[0][2] + rh.y * t[1][2] + rh.z * t[2][2];
	return v;
}

InertiaMatrix InertiaMatrix::operator+( const InertiaMatrix & rh ) const {
	return InertiaMatrix(*this) += rh;
} 

InertiaMatrix & InertiaMatrix::operator+=( const InertiaMatrix & rh ) {
	for (int i = 0; i < _countof(rows); i++) {
		for (int j = 0; j < 4; j++) {
			(*this)[i][j] += rh[i][j];
		}
	}
	return *this;
}

InertiaMatrix & InertiaMatrix::operator=( const InertiaMatrix & rh ) {
	memcpy(rows, rh.rows, sizeof(Float4) * _countof(rows));
	return *this;
}

bool InertiaMatrix::operator==( const InertiaMatrix & rh ) const {
	for (int i = 0; i < _countof(rows); i++) {
		for (int j = 0; j < 4; j++) {
			if ( (*this)[i][j] != rh[i][j] )
				return false;
		}
	}
	return true;
}

bool InertiaMatrix::operator!=( const InertiaMatrix & rh ) const {
	for (int i = 0; i < _countof(rows); i++) {
		for (int j = 0; j < 4; j++) {
			if ( (*this)[i][j] != rh[i][j] )
				return true;
		}
	}
	return false;
}

InertiaMatrix InertiaMatrix::Transpose() const {
	const InertiaMatrix & t = *this;
	return InertiaMatrix( t[0][0], t[1][0], t[2][0], t[3][0],
		t[0][1], t[1][1], t[2][1], t[3][1],
		t[0][2], t[1][2], t[2][2], t[3][2]);
}

Matrix33 InertiaMatrix::Submatrix( int skip_r, int skip_c ) const {
	Matrix33 sub;
	int i = 0, j = 0;
	for (int r = 0; r < _countof(rows); r++) {
		if (r == skip_r)
			continue;
		for (int c = 0; c < 4; c++) {
			if (c == skip_c)
				continue;
			sub[i][j] = (*this)[r][c];
			j++;
		}
		i++;
		j = 0;
	}
	return sub;
}

float InertiaMatrix::Adjoint( int skip_r, int skip_c ) const {
	Matrix33 sub = Submatrix( skip_r, skip_c );
	return pow(-1.0f, float(skip_r + skip_c)) * sub.Determinant();
}

InertiaMatrix InertiaMatrix::Inverse() const {
	InertiaMatrix result;

	float det = Determinant();
	for (int r = 0; r < _countof(rows); r++) {
		for (int c = 0; c < 4; c++) {
			result[c][r] = Adjoint(r, c) / det;
		}
	}

	return result;
}

float InertiaMatrix::Determinant() const {
	const InertiaMatrix & t = *this;
	return  t[0][0] * Submatrix(0, 0).Determinant()
		- t[0][1] * Submatrix(0, 1).Determinant()
		+ t[0][2] * Submatrix(0, 2).Determinant()
		- t[0][3] * Submatrix(0, 3).Determinant();
}

/*
 * ostream functions for printing with cout
 */
namespace Niflib {
ostream & operator<<( ostream & out, TexCoord const & val ) {
	return out << "(" << setw(6) << val.u << "," << setw(6) << val.v << ")";
}

ostream & operator<<( ostream & out, Triangle const & val ) {
	return out << "{" << setw(6) << val.v1 << "," << setw(6) << val.v2 << "," << setw(6) << val.v3 << "}";
}

ostream & operator<<( ostream & out, Vector3 const & val ) {
	return out << "(" << setw(6) << val.x << "," << setw(6) << val.y << "," << setw(6) << val.z << ")";
}

ostream & operator<<( ostream & out, Float2 const & val ) {
	return out << "{" << setw(6) << val.data[0] << "," << setw(6) << val.data[1] << "}";
}

ostream & operator<<( ostream & out, Matrix22 const & val ) {
	out << endl
		<< "   |" << setw(6) << val[0][0] << "," << setw(6) << val[0][1] << " |" << endl
		<< "   |" << setw(6) << val[1][0] << "," << setw(6) << val[1][1] << " |";
	return out;
}

ostream & operator<<( ostream & out, Float3 const & val ) {
	return out << "{" << setw(6) << val.data[0] << "," << setw(6) << val.data[1] << "," << setw(6) << val.data[2] << "}";
}

ostream & operator<<( ostream & out, Matrix33 const & val ) {
	out << endl
		<< "   |" << setw(6) << val[0][0] << "," << setw(6) << val[0][1] << "," << setw(6) << val[0][2] << " |" << endl
		<< "   |" << setw(6) << val[1][0] << "," << setw(6) << val[1][1] << "," << setw(6) << val[1][2] << " |" << endl
		<< "   |" << setw(6) << val[2][0] << "," << setw(6) << val[2][1] << "," << setw(6) << val[2][2] << " |";
	return out;
}

ostream & operator<<( ostream & out, Float4 const & val ) {
	return out << "{" << setw(6) << val.data[0] << "," << setw(6) << val.data[1] << "," << setw(6) << val.data[2] << "," << setw(6) << val.data[3] << "}";
}

ostream & operator<<( ostream & out, Matrix44 const & val ) {
	out << endl
		<< "   |" << setw(6) << val[0][0] << "," << setw(6) << val[0][1] << "," << setw(6) << val[0][2] << "," << setw(6) << val[0][3] << " |" << endl
		<< "   |" << setw(6) << val[1][0] << "," << setw(6) << val[1][1] << "," << setw(6) << val[1][2] << "," << setw(6) << val[1][3] << " |" << endl
		<< "   |" << setw(6) << val[2][0] << "," << setw(6) << val[2][1] << "," << setw(6) << val[2][2] << "," << setw(6) << val[2][3] << " |" << endl
		<< "   |" << setw(6) << val[3][0] << "," << setw(6) << val[3][1] << "," << setw(6) << val[3][2] << "," << setw(6) << val[3][3] << " |";
	return out;
}

ostream & operator<<( ostream & out, Color3 const & val ) {
	return out << "{R:" << setw(6) << val.r << " G:" << setw(6) << val.g << " B:" << setw(6) << val.b << "}";
}

ostream & operator<<( ostream & out, Color4 const & val ) {
	return out << "{R:" << setw(6) << val.r << " G:" << setw(6) << val.g << " B:" << setw(6) << val.b << " A:" << setw(6) << val.a << "}";
}

ostream & operator<<( ostream & out, Quaternion const & val ) {
	return out << "[" << setw(6) << val.w << ",(" << setw(6) << val.x << "," << setw(6) << val.y << "," << setw(6) << val.z << ")]";
}

ostream & operator<<( ostream & out, InertiaMatrix const & val ) {
	out << endl
		<< "   |" << setw(6) << val[0][0] << "," << setw(6) << val[0][1] << "," << setw(6) << val[0][2] << "," << setw(6) << val[0][3] << " |" << endl
		<< "   |" << setw(6) << val[1][0] << "," << setw(6) << val[1][1] << "," << setw(6) << val[1][2] << "," << setw(6) << val[1][3] << " |" << endl
		<< "   |" << setw(6) << val[2][0] << "," << setw(6) << val[2][1] << "," << setw(6) << val[2][2] << "," << setw(6) << val[2][3] << " |";
	return out;
}

}
