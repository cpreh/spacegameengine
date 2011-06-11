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


#ifndef SGE_RENDERER_GLSL_PROGRAM_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_GLSL_PROGRAM_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/glsl/program_parameters_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/optional_impl.hpp>
#include <utility>

namespace sge
{
namespace renderer
{
namespace glsl
{

class program_parameters
{
public:
	SGE_RENDERER_SYMBOL
	program_parameters();

	SGE_RENDERER_SYMBOL
	glsl::program_parameters &
	vertex_shader(
		sge::renderer::vertex_declaration const &,
		glsl::string const &
	);

	SGE_RENDERER_SYMBOL
	glsl::program_parameters &
	pixel_shader(
		glsl::string const &
	);
		
	SGE_RENDERER_SYMBOL
	glsl::program_parameters &
	geometry_shader(
		glsl::string const &
	);

	typedef fcppt::optional<
		std::pair<
			sge::renderer::vertex_declaration const *,
			glsl::string
		>
	> optional_vertex_shader;

	typedef fcppt::optional<
		glsl::string
	> optional_string;

	optional_vertex_shader const &
	vertex_shader() const;

	optional_string const &
	pixel_shader() const;

	optional_string const &
	geometry_shader() const;
private:
	optional_vertex_shader vertex_shader_;

	optional_string
		pixel_shader_,
		geometry_shader_;
};

}
}
}

#endif
