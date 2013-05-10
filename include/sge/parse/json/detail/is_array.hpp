/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PARSE_JSON_DETAIL_IS_ARRAY_HPP_INCLUDED
#define SGE_PARSE_JSON_DETAIL_IS_ARRAY_HPP_INCLUDED

#include <mizuiro/size_type.hpp>
#include <mizuiro/image/dimension_fwd.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/object_fwd.hpp>
#include <fcppt/math/vector/object_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/array.hpp>
#include <array>
#include <cstddef>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{
namespace detail
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template
<
	typename T
>
struct is_array
:
std::false_type
{
};

template
<
	typename T,
	std::size_t N
>
struct is_array
<
	std::array
	<
		T,
		N
	>
>
:
std::true_type
{
};

template
<
	typename T,
	std::size_t N
>
struct is_array
<
	boost::array
	<
		T,
		N
	>
>
:
std::true_type
{
};

template
<
	typename T,
	typename N,
	typename S
>
struct is_array
<
	fcppt::math::vector::object
	<
		T,
		N,
		S
	>
>
:
std::true_type
{
};

template
<
	typename T,
	typename N,
	typename S
>
struct is_array
<
	fcppt::math::dim::object
	<
		T,
		N,
		S
	>
>
:
std::true_type
{
};

template
<
	typename T,
	mizuiro::size_type N
>
struct is_array
<
	mizuiro::image::dimension
	<
		N,
		T
	>
>
:
std::true_type
{
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
