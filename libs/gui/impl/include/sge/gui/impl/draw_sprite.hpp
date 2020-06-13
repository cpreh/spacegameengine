//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_IMPL_DRAW_SPRITE_HPP_INCLUDED
#define SGE_GUI_IMPL_DRAW_SPRITE_HPP_INCLUDED

#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/state/no_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <fcppt/make_ref.hpp>


namespace sge
{
namespace gui
{
namespace impl
{

template<
	typename Choices
>
void
draw_sprite(
	sge::renderer::device::core &_renderer,
	sge::renderer::context::ffp &_context,
	sge::sprite::object<
		Choices
	> const &_sprite
)
{
	typedef
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			Choices
		>
	>
	sprite_buffers;

	typedef
	sge::sprite::state::no_choices
	state_choices;

	typedef
	sge::sprite::state::object<
		state_choices
	>
	sprite_state;

	typedef
	sge::sprite::state::parameters<
		state_choices
	>
	state_parameters;

	sprite_state state(
		fcppt::make_ref(
			_renderer
		),
		state_parameters()
	);

	sprite_buffers buffers(
		fcppt::make_ref(
			_renderer
		),
		sge::sprite::buffers::option::static_
	);

	sge::sprite::process::one(
		_context,
		_sprite,
		buffers,
		state
	);
}

}
}
}

#endif
