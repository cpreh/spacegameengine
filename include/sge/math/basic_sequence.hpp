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


#ifndef SGE_MATH_BASIC_SEQUENCE_HPP_INCLUDED
#define SGE_MATH_BASIC_SEQUENCE_HPP_INCLUDED

#include "../config.h"
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#endif
#include <boost/array.hpp>
#include <boost/foreach.hpp>
#include <iterator>
#include <cstddef>

#if !defined(SGE_HAVE_VARIADIC_TEMPLATES) && !defined(SGE_MATH_VECTOR_MAX_SIZE)
#define SGE_MATH_VECTOR_MAX_SIZE 4
#endif

namespace sge
{
namespace math
{

namespace detail
{
typedef std::size_t dim_type;
}

template<
	typename T,
	detail::dim_type Dim>
class basic_sequence {
public:
	typedef T                         value_type;
	typedef T&                        reference;
	typedef const T&                  const_reference;
	typedef T*                        pointer;
	typedef const T*                  const_pointer;
	typedef std::ptrdiff_t            difference_type;
	typedef detail::dim_type          size_type;
	typedef pointer                   iterator;
	typedef const_pointer             const_iterator;
	typedef std::reverse_iterator<
		iterator>                 reverse_iterator;
	typedef std::reverse_iterator<
		const_iterator>           const_reverse_iterator;

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	explicit basic_sequence(
		Args... args)
	{
	}
#else
//#define SGE_MATH_BASIC_SEQUENCE_CTOR_ASSIGN_N(z, n, text) (*this)[n] = text##n;
//#define SGE_MATH_BASIC_SEQUENCE_CTOR(z, n, text) basic_sequence(BOOST_PP_ENUM_PARAMS(BOOST_PP_ADD(n,1), T const& param)) { BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim); BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_BASIC_SEQUENCE_CTOR_ASSIGN_N, param) }
//	BOOST_PP_REPEAT(SGE_MATH_BASIC_SEQUENCE_MAX_SIZE, SGE_MATH_BASIC_SEQUENCE_CTOR, void)
#endif

#define SGE_MATH_BINARY_OP_ASSIGN_DECL(x) \
basic_sequence & operator x ( \
	basic_sequence const &r);

	SGE_MATH_BINARY_OP_ASSIGN_DECL(+=)
	SGE_MATH_BINARY_OP_ASSIGN_DECL(-=)
	SGE_MATH_BINARY_OP_ASSIGN_DECL(*=)
	SGE_MATH_BINARY_OP_ASSIGN_DECL(/=)
	SGE_MATH_BINARY_OP_ASSIGN_DECL(%=)
private:
	typedef boost::array<
		value_type,
		Dim>  internal_type;
	internal_type data_;
};

#define SGE_MATH_UNARY_OP_DECL(x) \
template< \
	typename T, \
	detail::dim_type Dim> \
basic_sequence<T, Dim> \
operator x( \
	basic_sequence<T, Dim> l);

SGE_MATH_UNARY_OP_DECL(+)
SGE_MATH_UNARY_OP_DECL(-)

#undef SGE_MATH_UNARY_OP_DECL

#define SGE_MATH_BINARY_OP_DECL(x) \
template< \
	typename T, \
	detail::dim_type Dim> \
basic_sequence<T, Dim> operator x ( \
	basic_sequence<T, Dim> const &l, \
	basic_sequence<T, Dim> const &r);

SGE_MATH_BINARY_OP_DECL(+)
SGE_MATH_BINARY_OP_DECL(-)
SGE_MATH_BINARY_OP_DECL(*)
SGE_MATH_BINARY_OP_DECL(/)
SGE_MATH_BINARY_OP_DECL(%)

#undef SGE_MATH_BINARY_OP_DECL

}
}

#endif
