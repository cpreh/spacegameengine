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


#ifndef SGE_MATH_BASIC_SEQUENCE_IMPL_HPP_INCLUDED
#define SGE_MATH_BASIC_SEQUENCE_IMPL_HPP_INCLUDED

#include "basic_sequence.hpp"
#include "compare.hpp"
#include "../array_facade_impl.hpp" // TODO: do we want this here?
#include <boost/static_assert.hpp>
#include <ostream>
#include <algorithm>

template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
sge::math::basic_sequence<T, Dim, Policy>::basic_sequence()
{}

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
template<typename... Args>
sge::math::basic_sequence<T, Dim, Policy>::basic_sequence(
	Args... args)
: Policy<T, Dim>(data())
{
	BOOST_STATIC_ASSERT(sizeof... (args) == Dim);
	init(args...);	
}
#else

#define SGE_MATH_BASIC_SEQUENCE_CTOR_ASSIGN_N(z, n, text)\
	(*this)[n] = text##n;

#define SGE_MATH_BASIC_SEQUENCE_CTOR(z, n, text)\
template< \
	typename T, \
	sge::math::detail::dim_type Dim, \
	template<typename, sge::math::detail::dim_type> class Policy> \
sge::math::basic_sequence<T, Dim, Policy>::basic_sequence(\
	BOOST_PP_ENUM_PARAMS(\
		BOOST_PP_ADD(n,1),\
		T const& param))\
: Policy<T, Dim>(data())\
{\
	BOOST_STATIC_ASSERT(BOOST_PP_ADD(n,1)==Dim);\
	BOOST_PP_REPEAT(BOOST_PP_ADD(n,1), SGE_MATH_BASIC_SEQUENCE_CTOR_ASSIGN_N, param)\
}

BOOST_PP_REPEAT(SGE_MATH_BASIC_SEQUENCE_MAX_SIZE, SGE_MATH_BASIC_SEQUENCE_CTOR, void)

#undef SGE_MATH_BASIC_SEQUENCE_CTOR_ASSIGN
#undef SGE_MATH_BASIC_SEQUENCE_CTOR

#endif

#define SGE_MATH_BINARY_OP_ASSIGN(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim, \
	template<typename, sge::math::detail::dim_type> class Policy> \
sge::math::basic_sequence<T, Dim, Policy> & \
sge::math::basic_sequence<T, Dim, Policy>::operator x( \
	basic_sequence<T, Dim, Policy> const &r) \
{ \
	for(detail::dim_type i(0); i < Dim; ++i) \
		(*this)[i] x r[i]; \
	return *this; \
}

SGE_MATH_BINARY_OP_ASSIGN(+=)
SGE_MATH_BINARY_OP_ASSIGN(-=)
SGE_MATH_BINARY_OP_ASSIGN(*=)
SGE_MATH_BINARY_OP_ASSIGN(/=)
SGE_MATH_BINARY_OP_ASSIGN(%=)

#undef SGE_MATH_BINARY_OP_ASSIGN

#define SGE_MATH_UNARY_OP(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim, \
	template<typename, sge::math::detail::dim_type> class Policy> \
sge::math::basic_sequence<T, Dim, Policy> \
sge::math::operator x( \
	basic_sequence<T, Dim, Policy> l) \
{ \
	for(unsigned i = 0; i < Dim; ++i) \
		l[i] = x l[i]; \
	return l; \
}

SGE_MATH_UNARY_OP(+)
SGE_MATH_UNARY_OP(-)

#undef SGE_MATH_UNARY_OP

#define SGE_MATH_BINARY_OP(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim, \
	template<typename, sge::math::detail::dim_type> class Policy> \
sge::math::basic_sequence<T, Dim, Policy> \
sge::math::operator x( \
	basic_sequence<T, Dim, Policy> l, \
	basic_sequence<T, Dim, Policy> const &r) \
{ \
	return l x##= r; \
}

SGE_MATH_BINARY_OP(+)
SGE_MATH_BINARY_OP(-)
SGE_MATH_BINARY_OP(*)
SGE_MATH_BINARY_OP(/)
SGE_MATH_BINARY_OP(%)

#undef SGE_MATH_BINARY_OP

#define SGE_MATH_BINARY_OP_SCALAR(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim, \
	template<typename, sge::math::detail::dim_type> class Policy> \
sge::math::basic_sequence<T, Dim, Policy> \
sge::math::operator x ( \
	basic_sequence<T, Dim, Policy> l, \
	typename basic_sequence<T, Dim, Policy>::const_reference r) \
{  \
	return l x##= r; \
}

SGE_MATH_BINARY_OP_SCALAR(+)
SGE_MATH_BINARY_OP_SCALAR(-)
SGE_MATH_BINARY_OP_SCALAR(/)
SGE_MATH_BINARY_OP_SCALAR(*)
SGE_MATH_BINARY_OP_SCALAR(%)

#define SGE_MATH_BINARY_OP_SCALAR_LEFT(x) \
template< \
	typename T, \
	sge::math::detail::dim_type Dim, \
	template<typename, sge::math::detail::dim_type> class Policy> \
sge::math::basic_sequence<T, Dim, Policy> \
sge::math::operator x ( \
	typename basic_sequence<T, Dim, Policy>::const_reference l, \
	basic_sequence<T, Dim, Policy> r) \
{ \
	return r x##= l; \
}

SGE_MATH_BINARY_OP_SCALAR_LEFT(+)
SGE_MATH_BINARY_OP_SCALAR_LEFT(-)
SGE_MATH_BINARY_OP_SCALAR_LEFT(*)

#undef SGE_MATH_BINARY_OP_SCALAR_LEFT

template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
typename sge::math::basic_sequence<T, Dim, Policy>::pointer
sge::math::basic_sequence<T, Dim, Policy>::data()
{
	return data_.c_array();
}

template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
typename sge::math::basic_sequence<T, Dim, Policy>::const_pointer
sge::math::basic_sequence<T, Dim, Policy>::data() const
{
	return data_.data();
}

template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
typename sge::math::basic_sequence<T, Dim, Policy>::size_type
sge::math::basic_sequence<T, Dim, Policy>::size() const
{
	return Dim;
}

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
template<typename... Args>
void sge::math::basic_sequence<T, Dim, Policy>::init(
	const_reference arg1,
	Args... args)
{
	init_where(0, arg1, args...);
}

template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
template<typename... Args>
void sge::math::basic_sequence<T, Dim, Policy>::init_where(
	size_type pos,
	const_reference arg1,
	Args... args)
{
	(*this)[pos] = arg1;
	init_where(++pos, args...);
}

template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
void sge::math::basic_sequence<T, Dim, Policy>::init_where(
	const size_type pos,
	const_reference arg)
{
	(*this)[pos] = arg;
}
#endif

template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
bool sge::math::operator==(
	basic_sequence<T, Dim, Policy> const &a,
	basic_sequence<T, Dim, Policy> const &b)
{
	return std::equal(
		a.begin(),
		a.end(),
		b.begin(),
		sge::math::compare<T>);
}

template<
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
bool sge::math::operator!=(
	basic_sequence<T, Dim, Policy> const &a,
	basic_sequence<T, Dim, Policy> const &b)
{
	return !(a == b);
}

template<
	typename D,
	typename S,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
sge::math::basic_sequence<D, Dim, Policy>
sge::math::structure_cast(basic_sequence<S, Dim, Policy> const &s)
{
	typedef basic_sequence<D, Dim, Policy> ret_type;
	ret_type ret;
	for(typename ret_type::size_type i = 0; i < Dim; ++i)
		ret[i] = static_cast<D>(s[i]);
	return ret;
}

template<
	typename CharT,
	typename CharTraits,
	typename T,
	sge::math::detail::dim_type Dim,
	template<typename, sge::math::detail::dim_type> class Policy>
std::basic_ostream<CharT, CharTraits> &
sge::math::operator << (
	std::basic_ostream<CharT, CharTraits> &s,
	basic_sequence<T, Dim, Policy> const &a)
{
	s << '(';
	for(typename basic_sequence<T, Dim, Policy>::size_type i(0); i < Dim-1; ++i)
		s << a[i] << ',';
	return s << a[Dim-1] << ')';
}

#endif
