//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_COORDINATES_RECT_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_COORDINATES_RECT_HPP_INCLUDED

#include <sge/sprite/detail/vf/texpos.hpp>
#include <sge/sprite/types/texture_coordinates.hpp>
#include <sge/sprite/types/basic/float_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/at.hpp>
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
	typename Choices,
	typename Iterator
>
void
fill_texture_coordinates_rect(
	Iterator _iterator,
	sge::sprite::types::texture_coordinates<
		typename Choices::type_choices
	> const &_rt
)
{
	typedef
	sge::sprite::types::basic::float_vector<
		typename Choices::type_choices
	>
	tex_pos;

	typedef
	brigand::at<
		typename
		sge::sprite::detail::vf::texpos<
			Choices
		>::type,
		Level
	>
	vertex_texpos;

	(*_iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			_rt.first.x(),
			_rt.first.y()
		)
	);

	(*_iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			_rt.second.x(),
			_rt.first.y()
		)
	);

	(*_iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			_rt.second.x(),
			_rt.second.y()
		)
	);

	(*_iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			_rt.first.x(),
			_rt.second.y()
		)
	);
}

}
}
}
}

#endif
