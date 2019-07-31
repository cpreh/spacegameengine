//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_PROCESS_ONE_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_ONE_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/one_with_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/render_context.hpp>


namespace sge
{
namespace sprite
{
namespace process
{

template<
	typename RenderContext,
	typename Choices,
	typename StateChoices,
	typename Buffers
>
inline
void
one(
	RenderContext &_render_context,
	sge::sprite::object<
		Choices
	> const &_sprite,
	Buffers &_buffers,
	sge::sprite::state::object<
		StateChoices
	> &_sprite_state
)
{
	sge::sprite::process::one_with_options<
		sge::sprite::process::options<
			sge::sprite::process::geometry_options::update
		>
	>(
		_render_context,
		_sprite,
		_buffers,
		_sprite_state,
		sge::sprite::state::default_options<
			StateChoices
		>()
	);
}

}
}
}

#endif
