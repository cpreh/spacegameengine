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
#include "../array_facade.hpp"
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#include <boost/static_assert.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#endif
#include <boost/array.hpp>
#include <iosfwd>
#include <cstddef>

#if !defined(SGE_HAVE_VARIADIC_TEMPLATES) && !defined(SGE_MATH_VECTOR_MAX_SIZE)
#define SGE_MATH_BASIC_SEQUENCE_MAX_SIZE 4
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
	detail::dim_type Dim,
	template<typename, detail::dim_type> class Policy>
class basic_sequence
: public array_facade<
	basic_sequence<T, Dim, Policy>,
	detail::dim_type,
	T&,
	T*,
	T*,
	T const*>,
  public Policy<T, Dim> {
private:
	typedef array_facade<
		basic_sequence<T, Dim, Policy>,
		detail::dim_type,
		T&,
		T*,
		T*,
		T const*> base_type;
public:
	typedef T                                          value_type;
	typedef typename base_type::reference              reference;
	typedef typename base_type::const_reference        const_reference;
	typedef typename base_type::pointer                pointer;
	typedef typename base_type::const_pointer          const_pointer;
	typedef std::ptrdiff_t                             difference_type;
	typedef typename base_type::size_type              size_type;
	typedef typename base_type::iterator               iterator;
	typedef typename base_type::const_iterator         const_iterator;
	typedef typename base_type::reverse_iterator       reverse_iterator;
	typedef typename base_type::const_reverse_iterator const_reverse_iterator;

	basic_sequence();

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	explicit basic_sequence(
		Args... args);
#else
#define SGE_MATH_BASIC_SEQUENCE_CTOR_DECL(z, n, text)\
	basic_sequence(\
		BOOST_PP_ENUM_PARAMS(\
			BOOST_PP_ADD(n,1),\
			T const& param));
	BOOST_PP_REPEAT(SGE_MATH_BASIC_SEQUENCE_MAX_SIZE, SGE_MATH_BASIC_SEQUENCE_CTOR_DECL, void)

#undef SGE_MATH_BASIC_SEQUENCE_CTOR_DECL
#endif

#define SGE_MATH_BINARY_OP_ASSIGN_DECL(x) \
basic_sequence & operator x ( \
	basic_sequence const &r);

	SGE_MATH_BINARY_OP_ASSIGN_DECL(+=)
	SGE_MATH_BINARY_OP_ASSIGN_DECL(-=)
	SGE_MATH_BINARY_OP_ASSIGN_DECL(*=)
	SGE_MATH_BINARY_OP_ASSIGN_DECL(/=)
	SGE_MATH_BINARY_OP_ASSIGN_DECL(%=)

#undef SGE_MATH_BINARY_OP_ASSIGN_DECL

#define SGE_MATH_BINARY_OP_SCALAR_ASSIGN_DECL(x) \
basic_sequence & operator x ( \
	const_reference r);

	SGE_MATH_BINARY_OP_SCALAR_ASSIGN_DECL(+=)
	SGE_MATH_BINARY_OP_SCALAR_ASSIGN_DECL(-=)
	SGE_MATH_BINARY_OP_SCALAR_ASSIGN_DECL(*=)
	SGE_MATH_BINARY_OP_SCALAR_ASSIGN_DECL(/=)
	SGE_MATH_BINARY_OP_SCALAR_ASSIGN_DECL(%=)

#undef SGE_MATH_BINARY_OP_SCALAR_ASSIGN_DECL

	pointer data();
	const_pointer data() const;

	size_type size() const;
private:
#ifdef SGE_HAVE_VARIADIC_TEMPLATES
	template<typename... Args>
	void init(
		const_reference arg1,
		Args... args);

	template<typename... Args>
	void init_where(
		size_type pos,
		const_reference arg1,
		Args... args);

	void init_where(
		size_type pos,
		const_reference arg);
#endif

	typedef boost::array<
		value_type,
		Dim>  internal_type;
	internal_type data_;
};

#define SGE_MATH_UNARY_OP_DECL(x) \
template< \
	typename T, \
	detail::dim_type Dim, \
	template<typename, detail::dim_type> class Policy> \
basic_sequence<T, Dim, Policy> \
operator x( \
	basic_sequence<T, Dim, Policy> l);

SGE_MATH_UNARY_OP_DECL(+)
SGE_MATH_UNARY_OP_DECL(-)

#undef SGE_MATH_UNARY_OP_DECL

#define SGE_MATH_BINARY_OP_DECL(x) \
template< \
	typename T, \
	detail::dim_type Dim, \
	template<typename, detail::dim_type> class Policy> \
basic_sequence<T, Dim, Policy> operator x ( \
	basic_sequence<T, Dim, Policy> l, \
	basic_sequence<T, Dim, Policy> const &r);

SGE_MATH_BINARY_OP_DECL(+)
SGE_MATH_BINARY_OP_DECL(-)
SGE_MATH_BINARY_OP_DECL(*)
SGE_MATH_BINARY_OP_DECL(/)
SGE_MATH_BINARY_OP_DECL(%)

#undef SGE_MATH_BINARY_OP_DECL

#define SGE_MATH_BINARY_OP_SCALAR_DECL(x) \
template< \
	typename T, \
	detail::dim_type Dim, \
	template<typename, detail::dim_type> class Policy> \
basic_sequence<T, Dim, Policy> operator x ( \
	basic_sequence<T, Dim, Policy> l, \
	typename basic_sequence<T, Dim, Policy>::const_reference r);

SGE_MATH_BINARY_OP_SCALAR_DECL(+)
SGE_MATH_BINARY_OP_SCALAR_DECL(-)
SGE_MATH_BINARY_OP_SCALAR_DECL(*)
SGE_MATH_BINARY_OP_SCALAR_DECL(/)
SGE_MATH_BINARY_OP_SCALAR_DECL(%)

#undef SGE_MATH_BINARY_OP_SCALAR_DECL

#define SGE_MATH_BINARY_OP_SCALAR_LEFT_DECL(x) \
template< \
	typename T, \
	detail::dim_type Dim, \
	template<typename, detail::dim_type> class Policy> \
basic_sequence<T, Dim, Policy> operator x ( \
	typename basic_sequence<T, Dim, Policy>::const_reference l, \
	basic_sequence<T, Dim, Policy> r);

SGE_MATH_BINARY_OP_SCALAR_LEFT_DECL(+)
SGE_MATH_BINARY_OP_SCALAR_LEFT_DECL(-)
SGE_MATH_BINARY_OP_SCALAR_LEFT_DECL(*)

#undef SGE_MATH_BINARY_OP_SCALAR_LEFT_DECL

template<
	typename T,
	detail::dim_type Dim,
	template<typename, detail::dim_type> class Policy> \
bool operator==(
	basic_sequence<T, Dim, Policy> const &,
	basic_sequence<T, Dim, Policy> const &);

template<
	typename T,
	detail::dim_type Dim,
	template<typename, detail::dim_type> class Policy> \
bool operator!=(
	basic_sequence<T, Dim, Policy> const &,
	basic_sequence<T, Dim, Policy> const &);

template<
	typename D,
	typename S,
	detail::dim_type Dim,
	template<typename, detail::dim_type> class Policy> \
basic_sequence<D, Dim, Policy>
structure_cast(basic_sequence<S, Dim, Policy> const &);

template<
	typename CharT,
	typename CharTraits,
	typename T,
	detail::dim_type Dim,
	template<typename, detail::dim_type> class Policy>
std::basic_ostream<CharT, CharTraits> &
operator << (
	std::basic_ostream<CharT, CharTraits> &,
	basic_sequence<T, Dim, Policy> const &);

}
}

#endif
