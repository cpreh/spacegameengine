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
#include "../exception.hpp"
#include "../text.hpp"
#include "../assert.hpp"
#include "dim_fwd.hpp"
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
 * dim uses variadic templates where available
 */
template<typename T, std::size_t Dim>
class dim {
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
	explicit dim(Args... args)
	{
		set(args...);
	}
#else
#define SGE_MATH_DIM_CTOR_ASSIGN_N(z, n, text) (*this)[n] = text##n;
#define SGE_MATH_DIM_CTOR(z, n, text) dim(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_DIM_CTOR_ASSIGN_N, param) }
	BOOST_PP_REPEAT(SGE_MATH_DIM_MAX_SIZE, SGE_MATH_DIM_CTOR, void)
#endif
	explicit dim()
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

	static dim const null()
	{
		dim ret;
		
		for(size_type i = 0; i < Dim; ++i)
			ret[i] = static_cast<value_type>(0);

		return ret;
	}

	/**
	 * Does range checking with an assertion
	 */
	reference operator[](const size_type pos)
	{
		SGE_ASSERT(pos < Dim);
		return data_[pos];
	}

	/**
	 * Does range checking with an assertion
	 */
	const_reference operator[](const size_type pos) const
	{
		SGE_ASSERT(pos < Dim);
		return data_[pos];
	}
	
	/**
	 * Does range checking with sge::exception
	 */
	reference at(const size_type pos)
	{
		if(pos >= Dim)
			throw exception(SGE_TEXT("dim<T, N>::at(): out of range!"));
		return (*this)[pos];
	}

	/**
	 * Does range checking with an exception
	 */
	const_reference at(const size_type pos) const
	{
		if(pos >= Dim)
			throw exception(SGE_TEXT("dim<T, N>::at(): out of range!"));
		return (*this)[pos];
	}

	/**
	 * Uses sge::math::compare to compare componentwise
	 */
	bool operator==(const dim& r) const
	{
		for(size_type i = 0; i < Dim; ++i)
			if (!compare(data_[i],r[i]))
				return false;
		return true;
	}

	/**
	 * Uses sge::math::compare to compare componentwise
	 */
	bool operator!=(const dim& r) const
	{
		return !((*this)==r);
	}

	dim& operator+=(const dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] += r[i];
		return *this;
	}

	dim& operator-=(const dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] -= r[i];
		return *this;
	}

	/**
	 * Multiplies componentwise
	 */
	dim& operator*=(const dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] *= r[i];
		return *this;
	}

	/**
	 * Divides componentwise
	 */
	dim& operator/=(const dim& r)
	{
		for(size_type i = 0; i < Dim; ++i)
			data_[i] /= r[i];
		return *this;
	}

	friend dim operator/(dim l, const_reference r)
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
		SGE_ASSERT(Dim > 2);
		return (*this)[2];
	}
	
	const_reference d() const
	{
		SGE_ASSERT(Dim > 2);
		return (*this)[2];
	}

	/*
	size_type dim() const
	{
		return Dim;
	}*/

	/**
	 * Returns the product of all components, so the length/area/volume/... of
	 * the dimension
	 */
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
dim<T,Dim> operator+(dim<T,Dim> l, const dim<T,Dim>& r)
{
	return l += r;
}

template<typename T, std::size_t Dim>
dim<T,Dim> operator-(dim<T,Dim> l, const dim<T,Dim>& r)
{
	return l -= r;
}

template<typename T, std::size_t Dim>
dim<T, Dim> operator*(dim<T,Dim> l, const dim<T,Dim>& r)
{
	return l *= r;
}

template<typename T, std::size_t Dim>
dim<T, Dim> operator/(dim<T,Dim> l, const dim<T,Dim>& r)
{
	return l /= r;
}

/**
 * Outputs the dim in the format \f$(v_0,\ldots,v_n)\f$.
 */
template<typename T, std::size_t Dim, typename Ch, typename Traits>
std::basic_ostream<Ch,Traits> &operator<<(std::basic_ostream<Ch,Traits> &stream,const dim<T,Dim> &v)
{
	stream << stream.widen('(');
	for(typename dim<T,Dim>::size_type i = 0; i < Dim-1; ++i)
		stream << v[i] << stream.widen(',');
	return stream << v[Dim-1] << stream.widen(')');
}

/**
 * Reads the vector from the stream in the format \f$(v_0,\ldots,v_n)\f$.
 */
template<typename T, std::size_t Dim, typename Ch, typename Traits>
std::basic_istream<Ch,Traits>& operator>>(std::basic_istream<Ch,Traits>& s, dim<T,Dim>& v)
{
	Ch c;
	s >> c;
	if(c != s.widen('('))
		s.setstate(std::ios_base::failbit);
	for(typename dim<T,Dim>::size_type i = 0; i < Dim-1; ++i)
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
 * Casts the dim<T> to dim<D> (using static_cast).
 */
template<typename D, typename S, std::size_t Dim>
dim<D, Dim> structure_cast(const dim<S, Dim>& r)
{
	typedef dim<D, Dim> ret_type;

	ret_type ret;
	for(typename ret_type::size_type i = 0; i < Dim; ++i)
		ret[i] = static_cast<D>(r[i]);
	return ret;
}

}
}

#endif

