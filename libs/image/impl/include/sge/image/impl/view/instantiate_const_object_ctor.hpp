/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_OBJECT_CTOR_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_OBJECT_CTOR_HPP_INCLUDED

#include <sge/image/impl/view/const_object_impl.hpp>
#include <sge/image/impl/view/format_macro.hpp>
#include <sge/src/core/export_function_instantiation.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <fcppt/config/external_end.hpp>


#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_OBJECT_CTOR(\
	format_arg,\
	args\
) \
template \
SGE_CORE_EXPORT_FUNCTION_INSTANTIATION \
sge::image::view::const_object< \
	BOOST_PP_TUPLE_ELEM(0, args), \
	BOOST_PP_TUPLE_ELEM(3, args) \
>::const_object( \
	BOOST_PP_TUPLE_ELEM(1, args)< \
		SGE_IMAGE_IMPL_VIEW_FORMAT_MACRO(BOOST_PP_TUPLE_ELEM(2, args), format_arg) \
	> ::type const & \
)

#endif
