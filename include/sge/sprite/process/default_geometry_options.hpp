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


#ifndef SGE_SPRITE_PROCESS_DEFAULT_GEOMETRY_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_DEFAULT_GEOMETRY_OPTIONS_HPP_INCLUDED

#include <sge/sprite/detail/process/do_default_sort.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace process
{

template<
	typename Choices,
	typename Compare,
	typename Enable = void
>
struct default_geometry_options;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Choices,
	typename Compare
>
struct default_geometry_options<
	Choices,
	Compare,
	typename boost::enable_if<
		sge::sprite::detail::process::do_default_sort<
			Choices,
			Compare
		>
	>::type
>
:
std::integral_constant<
	sge::sprite::process::geometry_options,
	sge::sprite::process::geometry_options::sort_and_update
>
{
};

template<
	typename Choices,
	typename Compare
>
struct default_geometry_options<
	Choices,
	Compare,
	typename boost::disable_if<
		sge::sprite::detail::process::do_default_sort<
			Choices,
			Compare
		>
	>::type
>
:
std::integral_constant<
	sge::sprite::process::geometry_options,
	sge::sprite::process::geometry_options::update
>
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
