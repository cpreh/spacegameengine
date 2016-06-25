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


#include <sge/opengl/parse_extensions.hpp>
#include <sge/opengl/glx/extension.hpp>
#include <sge/opengl/glx/extension_set.hpp>
#include <sge/opengl/glx/get_extensions.hpp>
#include <awl/backends/x11/default_screen.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::extension_set
sge::opengl::glx::get_extensions(
	awl::backends::x11::display const &_display
)
{
#if defined(GLX_VERSION_1_1)
	const char *const result(
		::glXQueryExtensionsString(
			_display.get(),
			awl::backends::x11::default_screen(
				_display
			).get()
		)
	);

	return
		result
		==
		nullptr
		?
			sge::opengl::glx::extension_set()
		:
			sge::opengl::parse_extensions<
				sge::opengl::glx::extension
			>(
				result
			)
		;
#else
	return
		sge::opengl::glx::extension_set();
#endif
}
