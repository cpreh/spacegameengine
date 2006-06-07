#ifndef SGE_VECTOR4_HPP_INCLUDED
#define SGE_VECTOR4_HPP_INCLUDED

#include "./vector3.hpp"

namespace sge
{
	template<typename T> class vector4 {
	public:
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		
		vector4(const_reference nx = value_type(), const_reference ny = value_type(), const_reference nz = value_type(), const_reference nw = value_type(1))
			: x(nx), y(ny), z(nz), w(nw) {}

		vector4(const vector3<T>& v)
		: x(v.x), y(v.y), z(v.z), w(1) {}

		vector4(const vector4& v)
		: x(v.x), y(v.y), z(v.z), w(v.w) {}

		vector4& operator= (const vector3<T>& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = value_type(1);
			return *this;
		}

		vector4& operator= (const vector4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
			return *this;
		}

		value_type x;
		value_type y;
		value_type z;
		value_type w;
	};

	template<typename T> inline bool operator== (const vector4<T>& l, const vector4<T>& r)
	{
		return l.x == r.x && l.y == r.y && l.z == r.z && l.w == r.w;
	}

	template<typename T> inline bool operator!= (const vector4<T>& l, const vector4<T>& r)
	{
		return !(l==r);
	}

	template<typename T> inline T dot_product (const vector4<T>& l, const vector4<T>& r)
	{
		return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
	}

	template<typename T, typename Ch, typename Traits> inline std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& s, const vector4<T>& v)
	{
		return s << '(' << v.x << ',' << v.y << ',' << v.z << ',' << v.w << ')';
	}
}

#endif
