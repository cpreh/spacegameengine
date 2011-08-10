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


#include <sge/renderer/glsl/program_parameters.hpp>
#include <utility>

sge::renderer::glsl::program_parameters::program_parameters()
:
	vertex_shader_(),
	pixel_shader_(),
	geometry_shader_()
{
}

sge::renderer::glsl::program_parameters &
sge::renderer::glsl::program_parameters::vertex_shader(
	sge::renderer::vertex_declaration const &_declaration,
	glsl::string const &_source
)
{
	vertex_shader_ =
		std::make_pair(
			&_declaration,
			_source
		);

	return *this;
}

sge::renderer::glsl::program_parameters &
sge::renderer::glsl::program_parameters::pixel_shader(
	glsl::string const &_source
)
{
	pixel_shader_ = _source;

	return *this;
}

sge::renderer::glsl::program_parameters &
sge::renderer::glsl::program_parameters::geometry_shader(
	glsl::string const &_source
)
{
	geometry_shader_ = _source;

	return *this;
}

sge::renderer::glsl::program_parameters::optional_vertex_shader const &
sge::renderer::glsl::program_parameters::vertex_shader() const
{
	return vertex_shader_;
}

sge::renderer::glsl::program_parameters::optional_string const &
sge::renderer::glsl::program_parameters::pixel_shader() const
{
	return pixel_shader_;
}

sge::renderer::glsl::program_parameters::optional_string const &
sge::renderer::glsl::program_parameters::geometry_shader() const
{
	return geometry_shader_;
}
