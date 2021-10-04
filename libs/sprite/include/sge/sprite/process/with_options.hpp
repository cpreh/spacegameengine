//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_PROCESS_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/detail/process/geometry.hpp>
#include <sge/sprite/process/is_options.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_fwd.hpp>
#include <sge/sprite/state/render_context.hpp>


namespace sge::sprite::process
{

template<
	typename Options,
	typename Range,
	typename Buffers,
	typename Compare,
	typename StateChoices
>
inline
void
with_options(
	sge::sprite::state::render_context<
		StateChoices
	> &_render_context,
	Range const &_range,
	Buffers &_buffers,
	Compare const &_compare,
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

	sge::sprite::render::range_with_options(
		_render_context,
		_buffers.vertex_declaration(),
		sge::sprite::detail::process::geometry<
			Options::geometry_options::value,
			typename Buffers::choices
		>(
			_range,
			_buffers,
			_compare
		),
		_states,
		_state_options
	);
}

}

#endif
