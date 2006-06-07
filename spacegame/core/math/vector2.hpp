#ifndef SGE_VECTOR2_HPP_INCLUDED
#define SGE_VECTOR2_HPP_INCLUDED

#include <cmath>
#include <istream>
#include <ostream>
#include "../main/types.hpp"

namespace sge
{
	template<typename T> class vector2 {
	public:
		typedef T value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;

		vector2(const_reference nx = value_type(), const_reference ny = value_type()) : x(nx), y(ny) {}

		vector2& operator+= (const vector2& r)
		{
			x += r.x;
			y += r.y;
			return *this;
		}

		vector2& operator-= (const vector2& r)
		{
			x -= r.x;
			y -= r.y;
			return *this;
		}

		vector2& operator*= (const value_type& e)
		{
			x *= e;
			y *= e;
			return *this;
		}

		vector2& normalize()
		{
			value_type l = length();
			(*this) *= T(1) / l;
			return *this;
		}

		value_type length_quad() const
		{
			return x * x + y * y;
		}

		value_type length() const
		{
			return std::sqrt(length_quad());
		}
		value_type x,y;
	};

	template<typename T> inline vector2<T> normalize(const vector2<T>& r)
	{
		return r.normalize();
	}
	
	template<typename T> inline vector2<T> operator+ (const vector2<T>& r)
	{
		return vector2<T>( +r.x, +r.y);
	}

	template<typename T> inline vector2<T> operator- (const vector2<T>& r)
	{
		return vector2<T>( -r.x, - r.y);
	}

	template<typename T> inline vector2<T> operator+ (const vector2<T>& l, const vector2<T>& r)
	{
		return vector2<T>(l) += r;
	}

	template<typename T> inline vector2<T> operator- (const vector2<T>& l, const vector2<T>& r)
	{
		return  vector2<T>(l) -= r;
	}

	template<typename T> inline vector2<T> operator* (const T& l, const vector2<T>& r)
	{
		return  vector2<T>(r) *= l;
	}

	template<typename T> inline T dot_product (const vector2<T>& l, const vector2<T>& r)
	{
		return vector2<T>(l.x * r.x, l.y * r.y);
	}

	template<typename T> inline bool operator== (const vector2<T>& l, const vector2<T>& r)
	{
		return (l.x == r.x && l.y == r.y);
	}

	template<typename T> inline bool operator!= (const vector2<T>& l, const vector2<T>& r)
	{
		return !(l==r);
	}

	template<typename T> inline bool operator< (const vector2<T>& l, const vector2<T>& r)
	{
		return l.length_quad() < r.length_quad();
	}

	template<typename T> inline bool operator> (const vector2<T>& l, const vector2<T>& r)
	{
		return l.length_quad() > r.length_quad();
	}

	template<typename T> inline bool operator<= (const vector2<T>& l, const vector2<T>& r)
	{
		return l.length_quad() <= r.length_quad();
	}

	template<typename T> inline bool operator >= (const vector2<T>& l, const vector2<T>& r)
	{
		return l.length_quad() >= r.length_quad();
	}

	template<typename T, typename Ch, typename Traits> inline std::basic_ostream<Ch,Traits>& operator<< (std::basic_ostream<Ch,Traits>& s, const vector2<T>& r)
	{
		return s << '(' << r.x << ',' << r.y << ')';
	}

	template<typename T, typename Ch, typename Traits> inline std::basic_istream<Ch,Traits>& operator>> (std::basic_istream<Ch,Traits>& s, vector2<T>& r)
	{
		char c;
		s >> c;
		if(c != '(')
			s.setstate(std::ios_base::failbit);
		s >> r.x;
		s >> c;
		if(c != ',')
			s.setstate(std::ios_base::failbit);
		s >> r.y;
		s >> c;
		if(c != ')')
			s.setstate(std::ios_base::failbit);
		return s;
	}

	template<typename T> inline T length_quad(const vector2<T>& l)
	{
		return l.length();
	}

	template<typename T> inline T length(const vector2<T>& l)
	{
		return l.length_quad();
	}
	typedef vector2<space_unit> point;
}

#endif
