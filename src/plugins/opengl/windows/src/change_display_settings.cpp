/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../change_display_settings.hpp"
#include <sge/log/global.hpp>
#include <sge/renderer/display_mode.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::windows::change_display_settings(
	renderer::display_mode const &_mode
)
{
	DEVMODE settings = { 0 };

	settings.dmSize = sizeof(DEVMODE);
	settings.dmPelsWidth = _mode.size().w();
	settings.dmPelsHeight = _mode.size().h();
	settings.dmBitsPerPel = static_cast<UINT>(_mode.bit_depth());
	settings.dmDisplayFrequency = _mode.refresh_rate().get();
	settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH|DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if(
		::ChangeDisplaySettings(
			&settings,
			CDS_FULLSCREEN
		)
		!= DISP_CHANGE_SUCCESSFUL
	)
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Cannot change resolution to ")
				<< _mode
				<< FCPPT_TEXT("! Reverting to window mode!")
		);
}
