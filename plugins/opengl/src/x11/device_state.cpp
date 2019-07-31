//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/x11/device_state.hpp>
#include <sge/opengl/x11/fullscreen.hpp>
#include <sge/opengl/x11/fullscreen_atom.hpp>
#include <sge/opengl/x11/state_atom.hpp>
#include <sge/opengl/xrandr/optional_system_ref.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/opengl/xrandr/state_unique_ptr.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/renderer/display_mode/fullscreen.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/window/object.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/to_optional.hpp>


sge::opengl::x11::device_state::device_state(
	fcppt::log::object &_log,
	sge::opengl::xrandr::optional_system_ref const &_xrandr_system,
	sge::renderer::display_mode::optional_fullscreen const &_fullscreen,
	sge::window::object &_window,
	sge::opengl::x11::state_atom const _wm_state,
	sge::opengl::x11::fullscreen_atom const _wm_fullscreen
)
:
	sge::opengl::platform::device_state(),
	log_{
		_log
	},
	xrandr_state_(
		fcppt::optional::map(
			_xrandr_system,
			[
				&_window
			](
				fcppt::reference<
					sge::opengl::xrandr::system
				> const _system
			)
			{
				return
					_system.get().create_state(
						_window
					);
			}
		)
	),
	wm_state_{
		_wm_state
	},
	wm_fullscreen_{
		_wm_fullscreen
	},
	window_{
		fcppt::cast::dynamic_exn<
			awl::backends::x11::window::base &
		>(
			_window.awl_object()
		)
	},
	resolution_()
{
	if(
		_fullscreen.has_value()
	)
		this->fullscreen(
			_fullscreen
		);
}

sge::opengl::x11::device_state::~device_state()
{
}

sge::renderer::display_mode::optional_object
sge::opengl::x11::device_state::display_mode() const
{
	return
		fcppt::optional::bind(
			xrandr_state_,
			[](
				xrandr_state_unique_ptr const &_state
			)
			{
				return
					_state->display_mode();
			}
		);
}

void
sge::opengl::x11::device_state::fullscreen(
	sge::renderer::display_mode::optional_fullscreen const &_opt_fullscreen
)
{
	auto const set_fullscreen(
		[
			this
		](
			bool const _value
		)
		{
			sge::opengl::x11::fullscreen(
				this->window_,
				this->wm_state_,
				this->wm_fullscreen_,
				_value
			);
		}
	);

	this->resolution_ =
		optional_resolution_unique_ptr();

	fcppt::optional::maybe(
		_opt_fullscreen,
		[
			&set_fullscreen
		]{
			set_fullscreen(
				false
			);
		},
		[
			&set_fullscreen,
			this
		](
			sge::renderer::display_mode::fullscreen const &_fullscreen
		)
		{
			set_fullscreen(
				true
			);

			this->resolution_ =
				fcppt::optional::bind(
					fcppt::variant::to_optional<
						sge::renderer::display_mode::object
					>(
						_fullscreen
					),
					[
						this
					](
						sge::renderer::display_mode::object const &_display_mode
					)
					{
						return
							fcppt::optional::maybe(
								this->xrandr_state_,
								[
									this
								]{
									FCPPT_LOG_ERROR(
										this->log_,
										fcppt::log::out
											<< FCPPT_TEXT("Xrandr was not found. Can't change the display mode.")
									)

									return
										optional_resolution_unique_ptr();
								},
								[
									&_display_mode
								](
									xrandr_state_unique_ptr const &_state
								){
									return
										optional_resolution_unique_ptr(
											_state->choose_resolution(
												_display_mode
											)
										);
								}
							);
					}
				);
		}
	);
}
