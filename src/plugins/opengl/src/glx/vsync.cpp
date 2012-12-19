/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/glx/current_drawable.hpp>
#include <sge/opengl/glx/proc_context.hpp>
#include <sge/opengl/glx/swap_context.hpp>
#include <sge/opengl/glx/vsync.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/logger.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/output.hpp>


void
sge::opengl::glx::vsync(
	sge::opengl::context::system::object &_system_context,
	awl::backends::x11::display &_display
)
{
	sge::opengl::glx::swap_context &context(
		sge::opengl::context::use<
			sge::opengl::glx::swap_context
		>(
			_system_context,
			sge::opengl::context::use<
				sge::opengl::glx::proc_context
			>(
				_system_context
			)
		)
	);

	if(
		!context.swap_interval_supported()
	)
	{
		FCPPT_LOG_ERROR(
			sge::renderer::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Setting vsync is not supported.")
		)

		return;
	}

	// prefer swap_interval_ext
	if(
		context.swap_interval_ext()
	)
	{
		FCPPT_LOG_INFO(
			sge::renderer::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Using glXSwapIntervalExt")
		);

		context.swap_interval_ext()(
			_display.get(),
			sge::opengl::glx::current_drawable(),
			1
		);

		return;
	}

	FCPPT_LOG_INFO(
		sge::renderer::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("Using glXSwapIntervalSGI")
	);

	if(
		context.swap_interval_sgi()(
			1
		)
		!= 0
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Setting the swap interval via SGI returned an error!")
		);
}
