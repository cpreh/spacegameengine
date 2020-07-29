//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/x11/device_state.hpp>
#include <sge/opengl/x11/system.hpp>
#include <sge/opengl/xrandr/create_system.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/x11/intern_atom.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <awl/backends/x11/system/object_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/deref.hpp>


sge::opengl::x11::system::system(
	fcppt::log::object_reference const _log,
	awl::backends::x11::system::object_ref const _awl_system
)
:
	log_{
		_log
	},
	xrandr_system_(
		sge::opengl::xrandr::create_system(
			_log,
			_awl_system.get().display()
		)
	),
	wm_state_{
		awl::backends::x11::intern_atom(
			_awl_system.get().display(),
			"_NET_WM_STATE"
		)
	},
	wm_fullscreen_{
		awl::backends::x11::intern_atom(
			_awl_system.get().display(),
			"_NET_WM_STATE_FULLSCREEN"
		)
	}
{
}

sge::opengl::x11::system::~system()
= default;

sge::opengl::platform::device_state_unique_ptr
sge::opengl::x11::system::create_device_state(
	sge::renderer::display_mode::optional_fullscreen const &_fullscreen,
	sge::window::object_ref const _window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::platform::device_state
		>(
			fcppt::make_unique_ptr<
				sge::opengl::x11::device_state
			>(
				this->log_,
				fcppt::optional::deref(
					this->xrandr_system_
				),
				_fullscreen,
				_window,
				this->wm_state_,
				this->wm_fullscreen_
			)
		);
}
