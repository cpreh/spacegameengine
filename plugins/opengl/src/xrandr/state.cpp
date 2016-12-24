/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/xrandr/choose_resolution.hpp>
#include <sge/opengl/xrandr/current_display_mode.hpp>
#include <sge/opengl/xrandr/display_modes.hpp>
#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/input_mask.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/opengl/xrandr/select_input.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/opengl/xrandr/update_configuration.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <awl/backends/x11/default_screen.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/root.hpp>
#include <awl/backends/x11/window/event/callback.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <awl/backends/x11/window/event/type.hpp>
#include <awl/window/object.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/dynamic_cross_exn.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/randr.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::state::state(
	sge::opengl::xrandr::extension const &_extension,
	awl::backends::x11::window::object &_window
)
:
	display_(
		_window.display()
	),
	window_(
		_window
	),
	config_(
		_window
	),
	display_mode_(),
	display_modes_(),
	change_connection_(
		// TODO: Change libawl so this is not needed
		fcppt::cast::static_downcast<
			awl::backends::x11::window::event::processor &
		>(
			fcppt::cast::dynamic_cross_exn<
				awl::window::object &
			>(
				window_
			).processor()
		).register_callback(
			awl::backends::x11::window::event::type(
				_extension.event_base().get()
				+
				RRScreenChangeNotify
			),
			awl::backends::x11::window::event::callback(
				std::bind(
					&sge::opengl::xrandr::state::event_callback,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	configure_connection_(
		fcppt::cast::static_downcast<
			awl::backends::x11::window::event::processor &
		>(
			fcppt::cast::dynamic_cross_exn<
				awl::window::object &
			>(
				window_
			).processor()
		).register_callback(
			awl::backends::x11::window::event::type(
				ConfigureNotify
			),
			awl::backends::x11::window::event::callback(
				std::bind(
					&sge::opengl::xrandr::state::event_callback,
					this,
					std::placeholders::_1
				)
			)
		)
	)
{
	// TODO: This could be wrapped like in sge::x11input
	sge::opengl::xrandr::select_input(
		display_,
		// TODO: root_window?
		*awl::backends::x11::window::root(
			display_,
			awl::backends::x11::default_screen(
				display_
			)
		),
		fcppt::strong_typedef_construct_cast<
			sge::opengl::xrandr::input_mask,
			fcppt::cast::size_fun
		>(
			RRScreenChangeNotifyMask
		)
	);

	this->update();
}

sge::opengl::xrandr::state::~state()
{
}

sge::renderer::display_mode::optional_object
sge::opengl::xrandr::state::display_mode() const
{
	return
		display_mode_;
}

sge::opengl::xrandr::resolution_unique_ptr
sge::opengl::xrandr::state::choose_resolution(
	sge::renderer::display_mode::object const &_display_mode
)
{
	return
		sge::opengl::xrandr::choose_resolution(
			config_,
			window_,
			_display_mode
		);
}

sge::renderer::display_mode::container
sge::opengl::xrandr::state::display_modes() const
{
	return
		display_modes_;
}

void
sge::opengl::xrandr::state::event_callback(
	awl::backends::x11::window::event::object const &_event
)
{
	if(
		sge::opengl::xrandr::update_configuration(
			_event
		)
	)
		this->update();
}

void
sge::opengl::xrandr::state::update()
{
	display_mode_ =
		sge::opengl::xrandr::current_display_mode(
			display_,
			window_
		);

	display_modes_ =
		sge::opengl::xrandr::display_modes(
			config_
		);
}
