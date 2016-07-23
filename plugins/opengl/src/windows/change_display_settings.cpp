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


#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::opengl::windows::change_display_settings(
	fcppt::log::object &_log,
	sge::renderer::display_mode::object const &_mode
)
{
	DEVMODE settings;

	ZeroMemory(
		&settings,
		sizeof(
			DEVMODE
		)
	);

	settings.dmSize = sizeof(DEVMODE);
	settings.dmPelsWidth = _mode.pixel_size().get().w();
	settings.dmPelsHeight = _mode.pixel_size().get().h();
	settings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

	fcppt::optional::maybe_void(
		_mode.refresh_rate(),
		[
			&settings
		](
			sge::renderer::display_mode::refresh_rate const _refresh_rate
		)
		{
			settings.dmDisplayFrequency = _refresh_rate.get();

			settings.dmFields |= DM_DISPLAYFREQUENCY;
		}
	);

	if(
		::ChangeDisplaySettings(
			&settings,
			CDS_FULLSCREEN
		)
		!=
		DISP_CHANGE_SUCCESSFUL
	)
		FCPPT_LOG_ERROR(
			_log,
			fcppt::log::_
				<< FCPPT_TEXT("Cannot change resolution to ")
				<< _mode
				<< FCPPT_TEXT("! Reverting to window mode!")
		);
}
