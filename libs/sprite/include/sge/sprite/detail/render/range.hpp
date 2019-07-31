//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_RENDER_RANGE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_RANGE_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/sprite/detail/render/inner.hpp>
#include <sge/sprite/detail/render/range_object.hpp>
#include <sge/sprite/detail/render/set_textures.hpp>
#include <sge/sprite/detail/render/unset_textures.hpp>
#include <sge/sprite/render/range_part_vector.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename Choices
>
void
range(
	sge::renderer::context::core &_render_context,
	sge::sprite::detail::render::range_object<
		Choices
	> const &_range_object,
	sge::sprite::render::range_part_vector<
		Choices
	> const &_range_parts
)
{
	for(
		auto const &element
		:
		_range_parts
	)
	{
		sge::sprite::detail::render::set_textures(
			_render_context,
			element
		);

		sge::sprite::detail::render::inner(
			_render_context,
			_range_object,
			element
		);
	}

	sge::sprite::detail::render::unset_textures<
		Choices
	>(
		_render_context
	);
}

}
}
}
}

#endif
