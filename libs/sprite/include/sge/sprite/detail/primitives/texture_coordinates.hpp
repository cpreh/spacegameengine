//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_COORDINATES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_COORDINATES_HPP_INCLUDED

#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/roles/texture_coordinates.hpp>
#include <sge/sprite/types/texture_coordinates_fwd.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices,
	typename Levels
>
struct texture_coordinates
{
private:
	template<
		typename Level
	>
	using
	make_role
	=
	fcppt::record::element<
		sge::sprite::roles::texture_coordinates<
			Level::value
		>,
		sge::sprite::types::texture_coordinates<
			typename
			Choices::type_choices
		>
	>;
public:
	using
	type
	=
	sge::sprite::detail::transform_texture_levels_static<
		metal::lambda<
			make_role
		>,
		Levels
	>;
};

}
}
}
}

#endif
