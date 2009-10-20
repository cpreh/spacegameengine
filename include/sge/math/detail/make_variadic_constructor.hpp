/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_HPP_INCLUDED
#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_HPP_INCLUDED

#include <sge/math/detail/initial_size.hpp>
#include <sge/math/detail/dim_matches.hpp>
#include <boost/static_assert.hpp>
#include <sge/config.h>
#ifndef SGE_HAVE_VARIADIC_TEMPLATES
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

#ifdef SGE_HAVE_VARIADIC_TEMPLATES
#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR(name) \
	SGE_MATH_DETAIL_TEMPLATE_PRE \
	template<\
		typename... Args\
	> \
	SGE_MATH_DETAIL_DEF_PRE::name(Args... args) \
	{ \
		::sge::math::detail::initial_size(\
			storage,\
			sizeof...(args)); \
		set_impl(0, args...); \
	} \
\
	SGE_MATH_DETAIL_TEMPLATE_PRE \
	template<\
		typename... Args,\
		typename Arg\
	> \
	void SGE_MATH_DETAIL_DEF_PRE::set_impl( \
		size_type const i, \
		Arg const &arg, \
		Args... args) \
	{ \
		*(data() + i) = arg; \
		set_impl(i + 1, args...); \
	} \
\
	SGE_MATH_DETAIL_TEMPLATE_PRE \
	template<\
		typename Arg\
	>\
	void SGE_MATH_DETAIL_DEF_PRE::set_impl( \
		size_type const i, \
		Arg const &arg) \
	{ \
		*(data() + i) = arg; \
	}
#else
#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_ASSIGN(z, n, text)\
*(data() + n) = text##n;

#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_IMPL(z, n, text)\
SGE_MATH_DETAIL_TEMPLATE_PRE \
SGE_MATH_DETAIL_DEF_PRE :: text(\
	BOOST_PP_ENUM_PARAMS(\
		BOOST_PP_INC(n),\
		T const& param\
	)\
)\
{\
	BOOST_STATIC_ASSERT((\
		math::detail::dim_matches<\
			BOOST_PP_INC(n),\
			dim_wrapper::value\
		>::value\
	));\
	\
	::sge::math::detail::initial_size(\
		storage,\
		n\
	); \
	\
	BOOST_PP_REPEAT(\
		BOOST_PP_INC(n),\
		SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_ASSIGN,\
		param\
	)\
}

#define SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR(\
	name\
)\
BOOST_PP_REPEAT(\
	SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_MAX_SIZE,\
	SGE_MATH_DETAIL_MAKE_VARIADIC_CONSTRUCTOR_IMPL,\
	name\
)

#endif

#endif
