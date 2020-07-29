//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/optional_refresh_rate.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/rotation.hpp>
#include <sge/opengl/xrandr/set_resolution.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


void
sge::opengl::xrandr::set_resolution(
	awl::backends::x11::window::base const &_window,
	sge::opengl::xrandr::configuration const &_config,
	sge::opengl::xrandr::mode_index const _mode_index,
	sge::opengl::xrandr::rotation const _rotation,
	sge::opengl::xrandr::optional_refresh_rate const &_refresh_rate
)
{
	fcppt::optional::maybe(
		_refresh_rate,
		[
			&_window,
			&_config,
			_mode_index,
			_rotation
		]{
			if(
				::XRRSetScreenConfig(
					_window.display().get().get(),
					_config.get(),
					_window.get(),
					_mode_index.get(),
					_rotation.get(),
					CurrentTime
				)
				!=
				0
			)
			{
				throw
					sge::renderer::exception{
						FCPPT_TEXT("Cannot change screen mode!")
					};
			}
		},
		[
			&_window,
			&_config,
			_mode_index,
			_rotation
		](
			sge::opengl::xrandr::refresh_rate const _rate
		)
		{
			if(
				::XRRSetScreenConfigAndRate(
					_window.display().get().get(),
					_config.get(),
					_window.get(),
					_mode_index.get(),
					_rotation.get(),
					_rate.get(),
					CurrentTime
				)
				!=
				0
			)
			{
				throw
					sge::renderer::exception{
						FCPPT_TEXT("Cannot change screen mode with rate!")
					};
			}
		}
	);
}
