#ifndef SGE_QUATERNION_HPP_INCLUDED
#define SGE_QUATERNION_HPP_INCLUDED

#include <cmath>
#include "./matrix4x4.hpp"

namespace sge
{
template<typename T> class quaternion {
public:
	typedef T value_type;

	quaternion(value_type x = value_type(), value_type y = value_type(), value_type z = value_type(), value_type w = value_type(1))
	: x(x), y(y), z(z), w(w) {}

	quaternion& operator+= (const quaternion& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;
		w += r.w;
		return *this;
	}

	quaternion& operator-= (const quaternion& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;
		w -= r.w;
		return *this;
	}

	quaternion& operator*= (const value_type& r)
	{
		x *= r;
		y *= r;
		z *= r;
		w *= r;
		return *this;
	}

	quaternion& operator*= (const quaternion& r)
	{
		const quaternion temp(w * r.x + x * r.w + y * r.z - z * r.y,
		                      w * r.y + y * r.w + z * r.x - x * r.z,
		                      w * r.z + z * r.w + x * r.y - y * r.x,
		                      w * r.w - x * r.x - y * r.y - z * r.z);
		return *this = temp;
	}

	value_type dot_product(const quaternion& r) const
	{
		return x * r.x + y * r.y + z * r.z + w * r.w;
	}

	matrix4x4<value_type> to_matrix() const
	{
		const value_type tx  = T(2) * x,
		                 ty  = T(2) * y,
		                 tz  = T(2) * z,
		                 twx = tx * w,
		                 twy = ty * w,
		                 twz = tz * w,
		                 txx = tx * x,
		                 txy = ty * x,
		                 txz = tz * x,
		                 tyy = ty * y,
		                 tyz = tz * y,
		                 tzz = tz * z;
		return matrix4x4<value_type>(1-(tyy+tzz), txy-twz,     txz+twy,      0,
		                             txy+twz,      1-(txx+tzz), tyz-twx,     0,
		                             txz-twy,      tyz+twx,     1-(txx+tyy), 0,
		                             0,            0,           0,           1);
	}

	quaternion operator+() const
	{
		return quaternion(+x,+y,+z,+w);
	}

	quaternion operator-() const
	{
		return quaternion(-x,-y,-z,-w);
	}

	value_type norm() const
	{
		return x*x + y*y + z*z;
	}

	quaternion inverse() const
	{
		const value_type n = norm();
		if(n > 0)
		{
			const value_type inv_n = value_type(1) / n;
			return quaternion(-x * inv_n, -y * inv_n, -z * inv_n, w * inv_n);
		}
		return identity();
	}

	bool operator==(const quaternion& r) const
	{
		return x == r.x && y == r.y && z == r.z && w == r.w;
	}

	static quaternion identity() { return quaternion(0,0,0,1); }
private:
	value_type x,y,z,w;
};

template<typename T> inline quaternion<T> quaternion_identity()
{
	return quaternion<T>::identity();
}

template<typename T> inline quaternion<T> from_axis(const vector3<T>& dir)
{
	using std::sin;
	using std::cos;
	const T cx = cos(dir.x * T(0.5)),
	        sx = sin(dir.x * T(0.5)),
	        cy = cos(dir.y * T(0.5)),
	        sy = sin(dir.y * T(0.5)),
	        cz = cos(dir.z * T(0.5)),
	        sz = sin(dir.z * T(0.5));

	return quaternion<T>(-sx * cy * cz - cx * sy * sz,
	                      cx * sy * cz - sx * cy * sz,
	                      sx * sy * cz - cx * cy * sz,
	                      cx * cy * cz + sx * sy * sz);
}

template<typename T> inline quaternion<T> from_axis_x(const T& x)
{
	return quaternion<T>(std::sin(x * T(0.5)),
	                     0,0,std::cos(x * T(0.5)));
}

template<typename T> inline quaternion<T> from_axis_y(const T& y)
{
	return quaternion<T>(0,
	                     std::sin(y * T(0.5)),
	                     0,
	                     std::cos(y * T(0.5)));
}

template<typename T> inline quaternion<T> from_axis_z(const T& z)
{
	return quaternion<T>(0,
	                     0,
	                     std::sin(z * T(0.5)),
	                     std::cos(z * T(0.5)));
}

template<typename T> inline quaternion<T> from_angle_axis(const T& p, const vector3<T>& axis)
{
	const T half_angle = T(0.5) * p;
	const T sinus = std::sin(half_angle);

	return quaternion<T>(sinus * axis.x,
	                     sinus * axis.y,
	                     sinus * axis.z,
	                     std::cos(half_angle));
}

template<typename T> inline matrix4x4<T> to_matrix(const quaternion<T>& q)
{
	return q.to_matrix();
}

template<typename T> inline quaternion<T> operator+ (const quaternion<T>& l, const quaternion<T>& r)
{
	return quaternion<T>(l) += r;
}

template<typename T> inline quaternion<T> operator- (const quaternion<T>& l, const quaternion<T>& r)
{
	return quaternion<T>(l) -= r;
}

template<typename T> inline quaternion<T> operator* (const quaternion<T>& l, const quaternion<T>& r)
{
	return quaternion<T>(l) *= r;
}

template<typename T> inline quaternion<T> operator* (const T& l, const quaternion<T>& r)
{
	return quaternion<T>(r) *= r;
}

template<typename T> inline T dot_product (const quaternion<T>& l, const quaternion<T>& r)
{
	return l.dot_product(r);
}

template<typename T> inline T norm(const quaternion<T>& q)
{
	q.norm();
}

template<typename T> inline quaternion<T> inverse (const quaternion<T>& q)
{
	return q.inverse();
}

template<typename T> inline bool operator!= (const quaternion<T>& l, const quaternion<T>& r)
{
	return !(l==r);
}

}

#endif

