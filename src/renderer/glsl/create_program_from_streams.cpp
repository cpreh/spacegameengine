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


#include <sge/renderer/glsl/create_program_from_streams.hpp>
#include <sge/renderer/glsl/create_program_from_strings.hpp>
#include <fcppt/optional_impl.hpp>
#include <sstream>

sge::renderer::glsl::program_ptr const
sge::renderer::glsl::create_program_from_streams(
	sge::renderer::device_ptr const _device,
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
		renderer::glsl::create_program_from_strings(
			_device,
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
