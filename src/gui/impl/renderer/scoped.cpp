#include <sge/gui/impl/renderer/scoped.hpp>
#include <sge/gui/impl/renderer/stateless.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/scoped_impl.hpp>


sge::gui::impl::renderer::scoped::scoped(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::context::ffp &_context
)
:
	sge::gui::impl::renderer::stateless(
		_renderer
	),
	state_(
		_renderer,
		sge::sprite::state::parameters<
			sprite_state_choices
		>()
	),
	scoped_state_(
		_renderer,
		_context,
		sge::sprite::state::default_options<
			sprite_state_choices
		>(),
		state_
	)
{
}

sge::gui::impl::renderer::scoped::~scoped()
{
}
