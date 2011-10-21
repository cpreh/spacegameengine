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


#include "../make_type.hpp"
#include "../../common.hpp"
#include "../../glew/is_supported.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


GLenum
sge::opengl::buffer::make_type(
	bool const _hardware_supported,
	glew::string const &_gl_version,
	GLenum const _normal_type,
	glew::string const &_extension,
	GLenum const _extension_type
)
{
	return
		_hardware_supported
		?
			glew::is_supported(
				_gl_version
			)
			?
				_normal_type
			:
				glew::is_supported(
					_extension
				)
				?
					_extension_type
				:
					throw sge::renderer::exception(
						FCPPT_TEXT("Should not happen.")
					)
		:
			_normal_type
		;
}
