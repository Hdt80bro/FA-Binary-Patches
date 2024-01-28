#pragma once

#include "global.h"

// adaptation of Wild Magic 3 from assembly reconstruction
// some of the original definitions were a little obtuse and been renamed

//namespace Wm3 {

template<class T>
struct Vector2
{	// 0x8 bytes
	T x,z;
};

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

template<class T>
struct Vector3
{	// 0xC bytes
	T x,y,z;
};

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

bool __cdecl isnan(double d)
#if RECOMPILE
{
    int lo = reinterpret_cast<int>(d);
    int hi = reinterpret_cast<long>(d) >> 32;
    return (hi & 0x7FF8) == 0x7FF0 && ((hi & 0x7FFFF) != 0 || lo) || (hi & 0x7FF8) == 0x7FF8;
}
#else
	asm("A83F03");
#endif

template<>
struct Vector3<float> {
    // note: not part of the library
	// 0x5657F0 BOOL __usercall Wm3::Vector3f::IsntNaN@<eax>(Wm3::Vector3f *this@<esi>)
	bool IsntNaN() const {
#if RECOMPILE
        return !isnan(x) && !isnan(y) && !isnan(z);
#else
		bool out;
		asm(
			"call 0x5657F0"
			: "=a"(out)
			: "S"(this)
			:
		);
		return out;
#endif
	}

	// 0x44F7E0 Wm3::Vector3f *__usercall Wm3::Vector3f::Normalize@<eax>(Wm3::Vector3f *this@<edi>, Wm3::Vector3f *dest@<esi>)
	Vector3f* Normalize(Vector3f* dest) const {
		Vector3f* out;
		asm(
			"call 0x5657F0"
			: "=a"(out)
			: "D"(this), "S"(dest)
			:
		);
		return out;
	}
};

template<class T>
Vector3<T> operator+(Vector3<T> vec1, Vector3<T> vec2) {
	return {
		vec1.x + vec2.x,
		vec1.y + vec2.y,
		vec1.z + vec2.z
	};
}
template<class T>
Vector3<T> operator-(Vector3<T> vec1, Vector3<T> vec2) {
	return {
		vec1.x - vec2.x,
		vec1.y - vec2.y,
		vec1.z - vec2.z
	};
}
template<class T>
Vector3<T> operator*(Vector3<T> vec, T scalar) {
	return {
		vec.x * scalar,
		vec.y * scalar,
		vec.z * scalar
	};
}

template<class Real>
struct Vector4
{	// 0x10 bytes
	Real x,y,z,w;
};
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;

template<class Real>
struct Quaternion
{	// 0x10 bytes
    //Real m_afTuple[4]; /*
	Real x,y,z,w;
    //*/
};

using Quaternionf = Quaternion<float>;
using Quaterniond = Quaternion<double>;

template<class Real>
struct Plane3
{
	Vector3<Real> Normal;
	Real Constant;
};
using Plane3f = Plane3<float>;
using Plane3d = Plane3<double>;


template<class Real>
struct Segment3
{
	Vector3<Real> Origin;
	Vector3<Real> Direction;
	Real Extent;
};
using Segment3f = Segment3<float>;
using Segment3d = Segment3<double>;

template<class Real, class TVector>
struct Distance
{
	void *vtable;
	int MaximumIterations;
	Real ZeroThreshold;
    Real m_fContactTime;
    TVector m_kClosestPoint0;
    TVector m_kClosestPoint1;
	bool m_bHasMultipleClosestPoints0;
	bool m_bHasMultipleClosestPoints1;
	Real m_fDifferenceStep;
	Real m_fInvTwoDifferenceStep;
};

using Distance3f = Distance<float, Vector3f>;

struct DistVector3Segment3f : Distance3f
{
 	const Vector3f& m_rkVector;
	const Segment3f& m_rkSegment;
};

template<class T>
struct AxisAlignedBox3 {
  Vector3<T> Min;
  Vector3<T> Max;
};

using AxisAlignedBox3f = AxisAlignedBox3<float>;
using AxisAlignedBox3d = AxisAlignedBox3<double>;



//} // namepsace Wm3