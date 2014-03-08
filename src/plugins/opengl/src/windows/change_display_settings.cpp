/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/logger.hpp>
#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <sge/src/include_windows.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


void
sge::opengl::windows::change_display_settings(
	sge::renderer::display_mode::object const &_mode
)
{
	DEVMODE settings = { 0 };

	settings.dmSize = sizeof(DEVMODE);
	settings.dmPelsWidth = _mode.pixel_size().get().w();
	settings.dmPelsHeight = _mode.pixel_size().get().h();
	settings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

	if(
		_mode.refresh_rate()
	)
	{
		settings.dmDisplayFrequency = _mode.refresh_rate()->get();

		settings.dmFields |= DM_DISPLAYFREQUENCY;
	}

	if(
		::ChangeDisplaySettings(
			&settings,
			CDS_FULLSCREEN
		)
		!= DISP_CHANGE_SUCCESSFUL
	)
		FCPPT_LOG_ERROR(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Cannot change resolution to ")
				<< _mode
				<< FCPPT_TEXT("! Reverting to window mode!")
		);
}
