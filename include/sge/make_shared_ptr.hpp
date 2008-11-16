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


#ifndef SGE_MAKE_SHARED_PTR_HPP_INCLUDED
#define SGE_MAKE_SHARED_PTR_HPP_INCLUDED

#include "shared_ptr.hpp"
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

namespace sge
{

#ifndef SGE_MAKE_SHARED_PTR_MAX_SIZE
#define SGE_MAKE_SHARED_PTR_MAX_SIZE 10
#endif

#define SGE_MAKE_SHARED_PTR_FUN(z, n, text)\
	template<\
		typename Type,\
		BOOST_PP_ENUM_PARAMS_Z(\
			z,\
			BOOST_PP_INC(n),\
			typename T)\
	>\
	shared_ptr<\
		Type\
	> const\
	make_shared_ptr(\
		BOOST_PP_ENUM_BINARY_PARAMS(\
			BOOST_PP_INC(n),\
			T,\
			const &param)\
		)\
	{\
		return shared_ptr<\
			Type\
		>(\
			new Type(\
				BOOST_PP_ENUM_PARAMS_Z(\
					z,\
					BOOST_PP_INC(n),\
					param)\
				)\
			);\
	}

BOOST_PP_REPEAT(SGE_MAKE_SHARED_PTR_MAX_SIZE, SGE_MAKE_SHARED_PTR_FUN, void)

template<
	typename Type
>
shared_ptr<
	Type
> const
make_shared_ptr()
{
	return shared_ptr<Type>(
		new Type());
}
// TODO: can't the macro generate this, too?

}

#endif
