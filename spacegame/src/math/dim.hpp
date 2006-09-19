#ifndef SGE_DIM_HPP_INCLUDED
#define SGE_DIM_HPP_INCLUDED

#include "../main/types.hpp"
#include "./vector2.hpp"

namespace sge
{

template<typename T>
struct basic_dim {
	typedef T value_type;
	basic_dim(const value_type& w = value_type(), const value_type& h = value_type())
		: w(w), h(h) {}
	explicit basic_dim(const vector2<T>& v)
		: w(v.x), h(v.y) {}
	value_type w,h;
};

template<typename T> basic_dim<T> operator+(const basic_dim<T>& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l.w+r.w,l.h+r.h);
}
template<typename T> basic_dim<T> operator-(const basic_dim<T>& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l.w-r.w,l.h-r.h);
}
template<typename T> basic_dim<T> operator*(const T& l, const basic_dim<T>& r)
{
	return basic_dim<T>(l*r.w,l*r.h);
}

typedef basic_dim<space_unit> dim;

}

#endif

