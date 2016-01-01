/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/glx/optional_raw_function.hpp>
#include <sge/opengl/glx/proc_address.hpp>
#include <sge/opengl/glx/proc_address_function.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/optional/from_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <string>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::optional_raw_function
sge::opengl::glx::proc_address(
	sge::opengl::glx::proc_address_function _proc_address,
	std::string const &_name
)
{
	return
		fcppt::optional::from_pointer(
			_proc_address(
				fcppt::cast::to_char_ptr<
					unsigned char const *
				>(
					_name.c_str()
				)
			)
		);
}
