//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/display_modes.hpp>
#include <sge/opengl/xrandr/make_display_mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/rates.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/sizes.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_concat.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::container
sge::opengl::xrandr::display_modes(
	sge::opengl::xrandr::configuration const &_config
)
{
	sge::opengl::xrandr::sizes const sizes{
		_config
	};

	return
		fcppt::algorithm::map_concat<
			sge::renderer::display_mode::container
		>(
			fcppt::make_int_range_count(
				sizes.size()
			),
			[
				&_config,
				&sizes
			](
				sge::opengl::xrandr::mode_index const _mode_index
			)
			{
				sge::opengl::xrandr::rates const rates{
					_config,
					_mode_index
				};

				XRRScreenSize const &cur_mode{
					sizes[
						_mode_index
					]
				};

				return
					fcppt::algorithm::map<
						sge::renderer::display_mode::container
					>(
						rates,
						[
							&cur_mode
						](
							short const _rate
						)
						{
							return
								sge::opengl::xrandr::make_display_mode(
									cur_mode,
									sge::opengl::xrandr::refresh_rate{
										_rate
									}
								);
						}
					);
			}
		);
}
