//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_COORDINATES_RECT_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_FILL_TEXTURE_COORDINATES_RECT_HPP_INCLUDED

#include <sge/renderer/vf/set_proxy.hpp>
#include <sge/renderer/vf/labels/texpos.hpp>
#include <sge/sprite/types/texture_coordinates.hpp>
#include <sge/sprite/types/basic/float_vector.hpp>
#include <fcppt/tuple/get.hpp>


namespace sge::sprite::geometry::detail
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
	using
	tex_pos
	=
	sge::sprite::types::basic::float_vector<
		typename Choices::type_choices
	>;

	using
	label
	=
	sge::renderer::vf::labels::texpos<
		Level::value
	>;

	auto const &first{
		fcppt::tuple::get<0>(
			_rt
		)
	};

	auto const &second{
		fcppt::tuple::get<1>(
			_rt
		)
	};

	sge::renderer::vf::set_proxy(
		*_iterator,
		label{},
		tex_pos(
			first.x(),
			first.y()
		)
	);

	++_iterator;

	sge::renderer::vf::set_proxy(
		*_iterator,
		label{},
		tex_pos(
			second.x(),
			first.y()
		)
	);

	++_iterator;

	sge::renderer::vf::set_proxy(
		*_iterator,
		label{},
		tex_pos(
			second.x(),
			second.y()
		)
	);

	++_iterator;

	sge::renderer::vf::set_proxy(
		*_iterator,
		label{},
		tex_pos(
			first.x(),
			second.y()
		)
	);
}

}

#endif
