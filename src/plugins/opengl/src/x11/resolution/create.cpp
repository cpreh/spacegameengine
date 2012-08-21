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


#include <sge/exception.hpp>
#include <sge/log/global.hpp>
#include <sge/opengl/x11/resolution/create.hpp>
#include <sge/opengl/x11/resolution/object.hpp>
#include <sge/opengl/x11/resolution/object_unique_ptr.hpp>
#include <sge/opengl/x11/resolution/xrandr_mode.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>


sge::opengl::x11::resolution::object_unique_ptr
sge::opengl::x11::resolution::create(
	awl::backends::x11::window::object &_window,
	sge::renderer::display_mode::optional_object const &_mode
)
{
	if(
		!_mode
	)
		return sge::opengl::x11::resolution::object_unique_ptr();

	try
	{
		return
			sge::opengl::x11::resolution::object_unique_ptr(
				fcppt::make_unique_ptr<
					sge::opengl::x11::resolution::xrandr_mode
				>(
					*_mode,
					fcppt::ref(
						_window
					)
				)
			);
	}
	catch(
		sge::exception const &_exception
	)
	{
		FCPPT_LOG_ERROR(
			log::global(),
			fcppt::log::_ << _exception.string()
		);
	}

	FCPPT_LOG_ERROR(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("sge cannot switch resolutions because ")
			<< FCPPT_TEXT("no known method worked!")
	);

	return
		sge::opengl::x11::resolution::object_unique_ptr();
}
