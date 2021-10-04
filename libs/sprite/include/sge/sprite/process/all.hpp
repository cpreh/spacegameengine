//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_PROCESS_ALL_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_ALL_HPP_INCLUDED

#include <sge/sprite/process/default_options.hpp>
#include <sge/sprite/process/with_options.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/render_context.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::process
{

template<
	typename Range,
	typename Buffers,
	typename Compare,
	typename StateChoices
>
void
all(
	sge::sprite::state::render_context<
		StateChoices
	> &_render_context,
	Range const &_range,
	Buffers &_buffers,
	Compare const &_compare,
	sge::sprite::state::object<
		StateChoices
	> &_states
)
{
	sge::sprite::process::with_options<
		sge::sprite::process::default_options<
			typename std::iterator_traits<
				typename Range::iterator
			>::value_type::choices,
			Compare
		>
	>(
		_render_context,
		_range,
		_buffers,
		_compare,
		_states,
		sge::sprite::state::default_options<
			StateChoices
		>()
	);
}

}

#endif
