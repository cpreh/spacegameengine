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


#include <sge/renderer/glsl/create_program.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <sge/renderer/glsl/program_parameters.hpp>
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <fcppt/optional_impl.hpp>

sge::renderer::glsl::program_ptr const
sge::renderer::glsl::create_program(
	sge::renderer::device &_device,
	glsl::program_parameters const &_parameters
)
{
	glsl::program_ptr const ret(
		_device.create_glsl_program()
	);

	if(
		glsl::program_parameters::optional_vertex_shader vertex_shader =
			_parameters.vertex_shader()
	)
	{
		ret->vertex_declaration(
			*vertex_shader->first
		);

		ret->vertex_shader(
			_device.create_glsl_vertex_shader(
				vertex_shader->second
			)
		);
	}
	
	if(
		glsl::program_parameters::optional_string const pixel_shader_source =
			_parameters.pixel_shader()
	)
		ret->pixel_shader(
			_device.create_glsl_pixel_shader(
				*pixel_shader_source
			)
		);

	if(
		glsl::program_parameters::optional_string const geometry_shader_source =
			_parameters.geometry_shader()
	)
		ret->geometry_shader(
			_device.create_glsl_geometry_shader(
				*geometry_shader_source
			)
		);

	ret->link();

	return ret;
}
