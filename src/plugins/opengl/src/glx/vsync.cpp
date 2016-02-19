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


#include <sge/opengl/logger.hpp>
#include <sge/opengl/glx/current_drawable.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <sge/opengl/glx/vsync.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::opengl::glx::vsync(
	sge::opengl::glx::swap_functions const &_swap_functions,
	awl::backends::x11::display &_display
)
{
	// prefer swap_interval_ext
	if(
		fcppt::optional::maybe(
			_swap_functions.swap_interval_ext(),
			fcppt::const_(
				false
			),
			[
				&_display
			](
				sge::opengl::glx::swap_functions::glx_swap_interval_ext_ref const _swap
			)
			{
				FCPPT_LOG_INFO(
					sge::opengl::logger(),
					fcppt::log::_
						<< FCPPT_TEXT("Using glXSwapIntervalExt")
				);

				_swap.get()(
					_display.get(),
					sge::opengl::glx::current_drawable(),
					1
				);

				return
					true;
			}
		)
	)
		return;

	if(
		fcppt::optional::maybe(
			_swap_functions.swap_interval_sgi(),
			fcppt::const_(
				false
			),
			[](
				sge::opengl::glx::swap_functions::glx_swap_interval_sgi_ref const _swap
			)
			{
				FCPPT_LOG_INFO(
					sge::opengl::logger(),
					fcppt::log::_
						<< FCPPT_TEXT("Using glXSwapIntervalSGI")
				);

				if(
					_swap.get()(
						1
					)
					!= 0
				)
					throw
						sge::renderer::exception{
							FCPPT_TEXT("Setting the swap interval via SGI returned an error!")
						};

				return
					true;
			}
		)
	)
		return;

	FCPPT_LOG_ERROR(
		sge::opengl::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("Setting vsync is not supported.")
	)
}
