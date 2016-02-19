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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_custom_texture_point_size.hpp>
#include <sge/sprite/detail/vf/texture_point_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
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
	typename Level,
	typename Iterator,
	typename Choices
>
inline
typename boost::enable_if<
	sge::sprite::detail::config::has_custom_texture_point_size<
		Choices
	>,
	void
>::type
fill_texture_point_size(
	Iterator const _iterator,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef typename boost::mpl::at<
		typename sge::sprite::detail::vf::texture_point_size<
			Choices
		>::type,
		Level
	>::type texture_point_size;

	(*_iterator). template set<
		texture_point_size
	>(
		typename texture_point_size::packed_type(
			_sprite. template texture_point_size_level<
				Level::value
			>()
		)
	);
}

template<
	typename Level,
	typename Iterator,
	typename Choices
>
inline
typename boost::disable_if<
	sge::sprite::detail::config::has_custom_texture_point_size<
		Choices
	>,
	void
>::type
fill_texture_point_size(
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
