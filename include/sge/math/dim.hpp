/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_MATH_DIM_HPP_INCLUDED
#define SGE_MATH_DIM_HPP_INCLUDED

#include "../config.h"
#include "../su.hpp"
#include "../exception.hpp"
#include "../text.hpp"
#include "../no_initialization_tag.hpp"
#include "compare.hpp"
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#endif
#include <iterator>
#include <ostream>
#include <istream>
#include <numeric>
#include <functional>
#include <cstddef>
#include <cassert>

#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#ifndef SGE_MATH_DIM_MAX_SIZE
#define SGE_MATH_DIM_MAX_SIZE 3
#endif
#endif

namespace sge
{
namespace math
{

/**
 * basic_dim uses variadic templates where available
 */
template<typename T, std::size_t Dim>
class basic_dim {
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
	BOOST_STATIC_ASSERT(Dim <= SGE_MATH_DIM_MAX_SIZE);
#endif
public:
	typedef T value_type;
	typedef T&             reference;
	typedef const T&       const_reference;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t    size_type;
	typedef T*             pointer;
	typedef const T*       const_pointer;
	typedef pointer        iterator;
	typedef const_pointer  const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	explicit basic_dim(Args... args)
	{
		set(args...);
	}
#else
#define SGE_MATH_DIM_CTOR_ASSIGN_N(z, n, text) (*this)[n] = text##n;
#define SGE_MATH_DIM_CTOR(z, n, text) basic_dim(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_DIM_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_DIM_MAX_SIZE, SGE_MATH_DIM_CTOR, void)
#endif
	/**
	 * This initializes the dim with zero
	 */
	basic_dim()
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] = 0;
	}

	/**
	 * This does not initialize any of the coordinates (models the built types)
	 */
	basic_dim(no_initialization_tag)
	{
	}

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	void set(const_reference arg, Args... args)
	{
		set_impl(0, arg, args...);
	}

private:
	template<typename... Args>
	void set_impl(const size_type i, const_reference arg, Args... args)
	{
		at(i) = arg;
		set_impl(i+1, args...);
	}

	void set_impl(const size_type i, const_reference arg)
	{
		at(i) = arg;
	}
public:
#else
#define SGE_MATH_DIM_SET(z, n, text) void set(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_DIM_CTOR_ASSIGN_N, param) }
BOOST_PP_REPEAT(SGE_MATH_DIM_MAX_SIZE, SGE_MATH_DIM_SET, void)
#endif

	/**
	 * Does range checking with an assertion
	 */
	reference operator[](const size_type pos)
	{
		assert(pos < Dim);
		return data_[pos];
	}

	/**
	 * Does range checking with an assertion
	 */
	const_reference operator[](const size_type pos) const
	{
		assert(pos < Dim);
		return data_[pos];
	}
	
	/**
	 * Does range checking with sge::exception
	 */
	reference at(const size_type pos)
	{
		if(pos >= Dim)
			throw exception(SGE_TEXT("basic_dim<T, N>::at(): out of range!"));
		return (*this)[pos];
	}

	/**
	 * Does range checking with an exception
	 */
	const_reference at(const size_type pos) const
	{
		if(pos >= Dim)
			throw exception(SGE_TEXT("basic_dim<T, N>::at(): out of range!"));
		return (*this)[pos];
	}

	/**
	 * Uses sge::math::compare to compare componentwise
	 */
	bool operator==(const basic_dim& r) const
	{
		for(size_type i = 0; i < Dim; ++i)
			if (!compare(data_[i],r[i]))
				return false;
		return true;
	}

	/**
	 * Uses sge::math::compare to compare componentwise
	 */
	bool operator!=(const basic_dim& r) const
	{
		return !((*this)==r);
	}

	basic_dim& operator+=(const basic_dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] += r[i];
		return *this;
	}

	basic_dim& operator-=(const basic_dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] -= r[i];
		return *this;
	}

	/**
	 * Multiplies componentwise
	 */
	basic_dim& operator*=(const basic_dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] *= r[i];
		return *this;
	}

	/**
	 * Divides componentwise
	 */
	basic_dim& operator/=(const basic_dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] /= r[i];
		return *this;
	}

	friend basic_dim operator/(basic_dim l, const_reference r)
	{
		for(size_type i = 0; i < Dim; ++i)
			l[i] /= r;
		return l;
	}

	reference w()
	{
		return (*this)[0];
	}

	const_reference w() const
	{
		return (*this)[0];
	}

	reference h()
	{
		return (*this)[1];
	}
	
	const_reference h() const
	{
		return (*this)[1];
	}

	reference d()
	{
		assert(Dim > 2);
		return (*this)[2];
	}
	
	const_reference d() const
	{
		assert(Dim > 2);
		return (*this)[2];
	}

	size_type dim() const
	{
		return Dim;
	}

	size_type content() const
	{
		return std::accumulate(begin(), end(), 1, std::multiplies<size_type>());
	}

	iterator begin()
	{
		return data_;
	}

	iterator end()
	{
		return &data_[Dim];
	}

	const_iterator begin() const
	{
		return data_;
	}

	const_iterator end() const
	{
		return &data_[Dim];
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return reverse_iterator(begin());
	}
private:
	T data_[Dim];
};

template<typename T, std::size_t Dim>
basic_dim<T,Dim> operator+(basic_dim<T,Dim> l, const basic_dim<T,Dim>& r)
{
	return l += r;
}

template<typename T, std::size_t Dim>
basic_dim<T,Dim> operator-(basic_dim<T,Dim> l, const basic_dim<T,Dim>& r)
{
	return l -= r;
}

template<typename T, std::size_t Dim>
basic_dim<T, Dim> operator*(basic_dim<T,Dim> l, const basic_dim<T,Dim>& r)
{
	return l *= r;
}

template<typename T, std::size_t Dim>
basic_dim<T, Dim> operator/(basic_dim<T,Dim> l, const basic_dim<T,Dim>& r)
{
	return l /= r;
}

/**
 * Outputs the dim in the format \f$(v_0,\ldots,v_n)\f$.
 */
template<typename T, std::size_t Dim, typename Ch, typename Traits>
std::basic_ostream<Ch,Traits> &operator<<(std::basic_ostream<Ch,Traits> &stream,const basic_dim<T,Dim> &v)
{
	stream << stream.widen('(');
	for(typename basic_dim<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		stream << v[i] << stream.widen(',');
	return stream << v[Dim-1] << stream.widen(')');
}

/**
 * Reads the vector from the stream in the format \f$(v_0,\ldots,v_n)\f$.
 */
template<typename T, std::size_t Dim, typename Ch, typename Traits>
std::basic_istream<Ch,Traits>& operator>>(std::basic_istream<Ch,Traits>& s, basic_dim<T,Dim>& v)
{
	Ch c;
	s >> c;
	if(c != s.widen('('))
		s.setstate(std::ios_base::failbit);
	for(typename basic_dim<T,Dim>::size_type i = 0; i < Dim-1; ++i)
	{
		s >> v[i] >> c;
		if (c != s.widen(','))
			s.setstate(std::ios_base::failbit);
	}
	s >> v[Dim-1] >> c;
	if (c != s.widen(')'))
		s.setstate(std::ios_base::failbit);
	return s;
}

/**
 * Casts the basic_dim<T> to basic_dim<D> (using static_cast).
 */
template<typename D, typename S, std::size_t Dim>
basic_dim<D, Dim> structure_cast(const basic_dim<S, Dim>& r)
{
	typedef basic_dim<D, Dim> ret_type;

	ret_type ret = ret_type(no_initialization_tag());
	for(typename ret_type::size_type i = 0; i < Dim; ++i)
		ret[i] = static_cast<D>(r[i]);
	return ret;
}

typedef basic_dim<space_unit,2> dim2;
typedef basic_dim<space_unit,3> dim3;

}
}

#endif

