//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/config_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/impl/any_visitor.hpp>
#include <sge/systems/impl/detail/instance_impl.hpp>


sge::systems::impl::any_visitor::any_visitor(
	sge::systems::detail::instance_impl &_impl
)
:
	impl_(
		_impl
	)
{
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::config const &
) const
{
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::detail::renderer const &_param
) const
{
	impl_.get().init_renderer(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::window const &_param
) const
{
	impl_.get().init_window_object(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::image2d const &_param
) const
{
	impl_.get().init_image2d(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::audio_loader const &_param
) const
{
	impl_.get().init_audio_loader(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::audio_player const &_param
) const
{
	impl_.get().init_audio_player(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::input const &_param
) const
{
	impl_.get().init_input(
		_param
	);
}

void
sge::systems::impl::any_visitor::operator()(
	sge::systems::font const &_param
) const
{
	impl_.get().init_font(
		_param
	);
}
