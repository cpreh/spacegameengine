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


#ifndef SGE_SHADER_OBJECT_PARAMETERS_HPP_INCLUDED
#define SGE_SHADER_OBJECT_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/shader/sampler_sequence.hpp>
#include <sge/shader/symbol.hpp>
#include <sge/shader/variable_sequence.hpp>
#include <sge/shader/vertex_format_string.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/string.hpp>
#include <string>
#include <vector>

namespace sge
{
namespace shader
{
class object_parameters
{
FCPPT_NONASSIGNABLE(
	object_parameters);
public:
	typedef
	std::vector<std::string>
	shader_sequence;

	SGE_SHADER_SYMBOL explicit
	object_parameters(
		renderer::device &,
		renderer::vertex_declaration const &,
		shader::vertex_format_string const &format_declaration,
		shader::variable_sequence const &variables,
		shader::sampler_sequence const &samplers);

	SGE_SHADER_SYMBOL object_parameters &
	vertex_shader(
		std::string const &);

	SGE_SHADER_SYMBOL object_parameters &
	vertex_shader(
		fcppt::filesystem::path const &);

	SGE_SHADER_SYMBOL object_parameters &
	fragment_shader(
		std::string const &);

	SGE_SHADER_SYMBOL object_parameters &
	fragment_shader(
		fcppt::filesystem::path const &);

	SGE_SHADER_SYMBOL object_parameters &
	name(
		fcppt::string const &);

	SGE_SHADER_SYMBOL renderer::device &
	renderer() const;

	SGE_SHADER_SYMBOL renderer::vertex_declaration const &
	vertex_declaration() const;

	SGE_SHADER_SYMBOL shader_sequence const &
	vertex_shaders() const;

	SGE_SHADER_SYMBOL shader_sequence const &
	fragment_shaders() const;

	SGE_SHADER_SYMBOL shader::vertex_format_string const &
	vertex_format_string() const;

	SGE_SHADER_SYMBOL shader::variable_sequence const &
	variables() const;

	SGE_SHADER_SYMBOL shader::sampler_sequence const &
	samplers() const;

	SGE_SHADER_SYMBOL fcppt::string const &
	name() const;

	SGE_SHADER_SYMBOL ~object_parameters();
private:
	renderer::device &renderer_;
	renderer::vertex_declaration const &vertex_declaration_;
	shader_sequence vertex_shaders_;
	shader_sequence fragment_shaders_;
	shader::vertex_format_string const vertex_format_string_;
	shader::variable_sequence const variables_;
	shader::sampler_sequence const samplers_;
	fcppt::string name_;
};
}
}

#endif
