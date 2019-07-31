//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_RENDER_UNSET_TEXTURE_STAGES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_UNSET_TEXTURE_STAGES_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/sprite/detail/apply_texture_levels.hpp>
#include <sge/sprite/detail/render/unset_texture_stage.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename TextureLevels
>
void
unset_texture_stages(
	sge::renderer::context::core &_render_context
)
{
	sge::sprite::detail::apply_texture_levels<
		TextureLevels
	>(
		sge::sprite::detail::render::unset_texture_stage(
			_render_context
		)
	);
}

}
}
}
}

#endif
