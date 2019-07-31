//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/windows/change_display_settings.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/output.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
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
			fcppt::log::out
				<< FCPPT_TEXT("Cannot change resolution to ")
				<< _mode
				<< FCPPT_TEXT("! Reverting to window mode!")
		);
}
