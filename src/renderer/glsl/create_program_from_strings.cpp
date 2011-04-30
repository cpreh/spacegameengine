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


#include <sge/renderer/glsl/create_program_from_strings.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/device.hpp>
#include <fcppt/optional_impl.hpp>

sge::renderer::glsl::program_ptr const
sge::renderer::glsl::create_program_from_strings(
	sge::renderer::device &_device,
	glsl::optional_string const &_vertex_shader_source,
	glsl::optional_string const &_pixel_shader_source
)
{
	glsl::program_ptr const ret(
		_device.create_glsl_program()
	);

	if(
		_vertex_shader_source
	)
		ret->vertex_shader(
			_device.create_glsl_vertex_shader(
				*_vertex_shader_source
			)
		);
	
	if(
		_pixel_shader_source
	)
		ret->pixel_shader(
			_device.create_glsl_pixel_shader(
				*_pixel_shader_source
			)
		);

	ret->link();

	return ret;
}
