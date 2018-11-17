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


#include <sge/renderer/display_mode/draw_timer_setting.hpp>
#include <sge/renderer/display_mode/draw_timer_setting_opt.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/timer/setting.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/map.hpp>


awl::timer::setting
sge::renderer::display_mode::draw_timer_setting_opt(
	fcppt::log::object &_log,
	sge::renderer::display_mode::optional_object const &_opt_display_mode
)
{
	return
		fcppt::optional::from(
			fcppt::optional::bind(
				_opt_display_mode,
				[
					&_log
				](
					sge::renderer::display_mode::object const &_display_mode
				)
				{
					return
						fcppt::optional::map(
							_display_mode.refresh_rate(),
							[
								&_log
							](
								sge::renderer::display_mode::refresh_rate const _rate
							)
							{
								awl::timer::setting const result{
									sge::renderer::display_mode::draw_timer_setting(
										_rate
									)
								};

								FCPPT_LOG_INFO(
									_log,
									fcppt::log::out
										<<
										FCPPT_TEXT("Using draw interval of ")
										<<
										result.period().get().count()
										<<
										FCPPT_TEXT(" milliseconds")
								);

								return
									result;
							}
						);
				}
			),
			[
				&_log
			]{
				FCPPT_LOG_WARNING(
					_log,
					fcppt::log::out
						<<
						FCPPT_TEXT("Cannot determine display refresh rate -")
						<<
						FCPPT_TEXT(" using a refresh rate of 60.")
				);

				return
					sge::renderer::display_mode::draw_timer_setting(
						sge::renderer::display_mode::refresh_rate{
							60u
						}
					);
			}
		);
}
