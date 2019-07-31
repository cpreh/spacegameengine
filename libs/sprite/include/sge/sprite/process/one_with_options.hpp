//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_PROCESS_ONE_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_ONE_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/geometry/make_single_range.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/is_options.hpp>
#include <sge/sprite/process/with_options.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_fwd.hpp>


namespace sge
{
namespace sprite
{
namespace process
{

template<
	typename Options,
	typename RenderContext,
	typename Choices,
	typename Buffers,
	typename StateChoices
>
inline
void
one_with_options(
	RenderContext &_render_context,
	sge::sprite::object<
		Choices
	> const &_sprite,
	Buffers &_buffers,
	sge::sprite::state::object<
		StateChoices
	> &_states,
	sge::sprite::state::options<
		StateChoices
	> const &_state_options
)
{
	static_assert(
		sge::sprite::process::is_options<
			Options
		>::value,
		"Options must be a sprite::process::options"
	);

	static_assert(
		Options::geometry_options::value
		!=
		sge::sprite::process::geometry_options::sort_and_update,
		"This function can't be used with geometry_options::sort_and_udpate"
	);

	sge::sprite::process::with_options<
		Options
	>(
		_render_context,
		sge::sprite::geometry::make_single_range(
			_sprite
		),
		_buffers,
		sge::sprite::compare::nothing(),
		_states,
		_state_options
	);
}

}
}
}

#endif
