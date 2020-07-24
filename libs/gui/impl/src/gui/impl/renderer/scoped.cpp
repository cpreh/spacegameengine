//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/impl/renderer/scoped.hpp>
#include <sge/gui/impl/renderer/stateless.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/scoped_impl.hpp>
#include <fcppt/reference_to_base.hpp>


sge::gui::impl::renderer::scoped::scoped(
	sge::renderer::device::ffp_ref const _renderer,
	sge::renderer::context::ffp_ref const _context
)
:
	sge::gui::impl::renderer::stateless(
		fcppt::reference_to_base<
			sge::renderer::device::core
		>(
			_renderer
		)
	),
	state_(
		_renderer,
		sge::sprite::state::parameters<
			sprite_state_choices
		>()
	),
	scoped_state_(
		_renderer.get(),
		_context,
		sge::sprite::state::default_options<
			sprite_state_choices
		>(),
		state_
	)
{
}

sge::gui::impl::renderer::scoped::~scoped()
= default;
