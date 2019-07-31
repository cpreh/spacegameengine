//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/current_mode.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/rotation.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::mode
sge::opengl::xrandr::current_mode(
	sge::opengl::xrandr::configuration const &_config
)
{
	Rotation cur_rotation;

	SizeID const cur_size(
		::XRRConfigCurrentConfiguration(
			_config.get(),
			&cur_rotation
		)
	);

	short const rate(
		::XRRConfigCurrentRate(
			_config.get()
		)
	);

	return
		sge::opengl::xrandr::mode(
			sge::opengl::xrandr::mode_index{
				static_cast<
					int
				>(
					cur_size
				)
			},
			sge::opengl::xrandr::rotation{
				cur_rotation
			},
			sge::opengl::xrandr::refresh_rate{
				rate
			}
		);
}
