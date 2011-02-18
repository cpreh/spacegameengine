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


#include <sge/renderer/device.hpp>
#include <sge/renderer/glsl/program.hpp>
#include <fcppt/optional_impl.hpp>
#include <sstream>

sge::renderer::device::device()
{
}

sge::renderer::glsl::program_ptr const
sge::renderer::device::create_glsl_program(
	glsl::optional_string const &_vertex_shader_source,
	glsl::optional_string const &_pixel_shader_source
)
{
	glsl::program_ptr const ret(
		this->create_glsl_program()
	);

	if(
		_vertex_shader_source
	)
		ret->vertex_shader(
			this->create_glsl_vertex_shader(
				*_vertex_shader_source
			)
		);
	
	if(
		_pixel_shader_source
	)
		ret->pixel_shader(
			this->create_glsl_pixel_shader(
				*_pixel_shader_source
			)
		);

	ret->link();

	return ret;
}

sge::renderer::glsl::program_ptr const
sge::renderer::device::create_glsl_program(
	glsl::optional_istream const &_vertex_shader_source,
	glsl::optional_istream const &_pixel_shader_source
)
{
	typedef std::basic_ostringstream<
		renderer::glsl::char_type
	> osstream;

	osstream
		vs_stream,
		ps_stream;

	if(
		_vertex_shader_source
	)
		vs_stream << _vertex_shader_source->get().rdbuf();

	if(
		_pixel_shader_source
	)
		ps_stream << _pixel_shader_source->get().rdbuf();

	return
		this->create_glsl_program(
			_vertex_shader_source
			?
				vs_stream.str()
			:
				renderer::glsl::optional_string(),
			_pixel_shader_source
			?
				ps_stream.str()
			:
				renderer::glsl::optional_string()
		);
}

sge::renderer::device::~device()
{
}
