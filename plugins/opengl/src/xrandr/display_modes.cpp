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
