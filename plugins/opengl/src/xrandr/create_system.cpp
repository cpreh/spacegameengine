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


#include <sge/opengl/xrandr/create_system.hpp>
#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/get_extension.hpp>
#include <sge/opengl/xrandr/get_version.hpp>
#include <sge/opengl/xrandr/optional_system_unique_ptr.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/opengl/xrandr/version.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/event/processor_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>


sge::opengl::xrandr::optional_system_unique_ptr
sge::opengl::xrandr::create_system(
	fcppt::log::object &_log,
	awl::backends::x11::display &_display
)
{
	return
		fcppt::optional::maybe(
			sge::opengl::xrandr::get_extension(
				_display
			),
			[
				&_log
			]{
				FCPPT_LOG_WARNING(
					_log,
					fcppt::log::_
						<< FCPPT_TEXT("xrandr extension not found")
				);

				return
					sge::opengl::xrandr::optional_system_unique_ptr();
			},
			[
				&_log,
				&_display
			](
				sge::opengl::xrandr::extension const _extension
			)
			{
				sge::opengl::xrandr::version const version(
					sge::opengl::xrandr::get_version(
						_extension,
						_display
					)
				);

				if(
					version
					<
					sge::opengl::xrandr::version(
						1,
						3
					)
				)
				{
					FCPPT_LOG_WARNING(
						_log,
						fcppt::log::_
							<< FCPPT_TEXT("xrandr version ")
							<< version
							<< FCPPT_TEXT(" too old")
					);

					return
						sge::opengl::xrandr::optional_system_unique_ptr();
				}

				return
					sge::opengl::xrandr::optional_system_unique_ptr(
						fcppt::make_unique_ptr<
							sge::opengl::xrandr::system
						>(
							_extension
						)
					);
			}
		);
}
