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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_INDICES_PER_SPRITE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_INDICES_PER_SPRITE_HPP_INCLUDED

#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <sge/sprite/geometry/detail/count_constant.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Choices,
	typename Enable = void
>
struct indices_per_sprite;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Choices
>
struct indices_per_sprite<
	Choices,
	typename boost::enable_if<
		sge::sprite::detail::config::needs_index_buffer<
			Choices
		>
	>::type
>
:
sge::sprite::geometry::detail::count_constant<
	6U
>
{
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
