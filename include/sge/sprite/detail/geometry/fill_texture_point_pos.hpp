/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_FILL_TEXTURE_POINT_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_FILL_TEXTURE_POINT_POS_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_custom_texture_point_pos.hpp>
#include <sge/sprite/detail/vf/texture_point_pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Level,
	typename Iterator,
	typename Choices
>
typename boost::enable_if<
	sge::sprite::detail::config::has_custom_texture_point_pos<
		Choices
	>,
	void
>::type
fill_texture_point_pos(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef typename boost::mpl::at<
		typename sge::sprite::detail::vf::texture_point_pos<
			Choices
		>::type,
		Level
	>::type texture_point_pos;

	(*_iterator). template set<
		texture_point_pos
	>(
		_sprite. template texture_point_pos_level<
			Level::value
		>()
	);
}

template<
	typename Level,
	typename Iterator,
	typename Choices
>
typename boost::disable_if<
	sge::sprite::detail::config::has_custom_texture_point_pos<
		Choices
	>,
	void
>::type
fill_texture_point_pos(
	Iterator,
	sge::sprite::object<
		Choices
	> const &
)
{
}

}
}
}
}

#endif
