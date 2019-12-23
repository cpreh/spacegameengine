//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_RENDER_UNSET_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_UNSET_TEXTURES_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/sprite/detail/config/has_texture_levels.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <sge/sprite/detail/render/unset_texture_stages.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


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
std::enable_if_t<
	sge::sprite::detail::config::has_texture_levels<
		Choices
	>::value,
	void
>
unset_textures(
	sge::renderer::context::core &_render_context
)
{
	sge::sprite::detail::render::unset_texture_stages<
		sge::sprite::detail::config::texture_levels<
			Choices
		>
	>(
		_render_context
	);
}

template<
	typename Choices
>
std::enable_if_t<
	fcppt::not_(
		sge::sprite::detail::config::has_texture_levels<
			Choices
		>::value
	),
	void
>
unset_textures(
	sge::renderer::context::core &
)
{
}

}
}
}
}

#endif
