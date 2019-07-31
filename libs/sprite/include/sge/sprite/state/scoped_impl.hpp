//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_SCOPED_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_SCOPED_IMPL_HPP_INCLUDED

#include <sge/sprite/state/scoped_decl.hpp>
#include <sge/sprite/state/set.hpp>
#include <sge/sprite/state/unset.hpp>


template<
	typename StateChoices
>
sge::sprite::state::scoped<
	StateChoices
>::scoped(
	render_device &_render_device,
	render_context &_render_context,
	state_options const &_options,
	state_object &_object
)
:
	render_context_(
		_render_context
	),
	options_(
		_options
	)
{
	sge::sprite::state::set(
		_render_device,
		render_context_,
		options_,
		_object
	);
}

template<
	typename StateChoices
>
sge::sprite::state::scoped<
	StateChoices
>::~scoped()
{
	sge::sprite::state::unset(
		render_context_,
		options_
	);
}

#endif
