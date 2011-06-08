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


#include <sge/shader/object_parameters.hpp>

sge::shader::object_parameters::object_parameters(
	renderer::device &_renderer,
	renderer::vertex_declaration const &_vertex_declaration,
	fcppt::filesystem::path const &_vertex_file,
	fcppt::filesystem::path const &_fragment_file,
	shader::vertex_format_string const &_vertex_format_string,
	shader::variable_sequence const &_variables,
	shader::sampler_sequence const &_samplers)
:
	renderer_(
		_renderer),
	vertex_declaration_(
		_vertex_declaration),
	vertex_file_(
		_vertex_file),
	fragment_file_(
		_fragment_file),
	vertex_format_string_(
		_vertex_format_string),
	variables_(
		_variables),
	samplers_(
		_samplers)
{
}

sge::renderer::device &
sge::shader::object_parameters::renderer() const
{
	return renderer_;
}

sge::renderer::vertex_declaration const &
sge::shader::object_parameters::vertex_declaration() const
{
	return vertex_declaration_;
}

fcppt::filesystem::path const &
sge::shader::object_parameters::vertex_file() const
{
	return vertex_file_;
}

fcppt::filesystem::path const &
sge::shader::object_parameters::fragment_file() const
{
	return fragment_file_;
}

sge::shader::vertex_format_string const &
sge::shader::object_parameters::vertex_format_string() const
{
	return vertex_format_string_;
}

sge::shader::variable_sequence const &
sge::shader::object_parameters::variables() const
{
	return variables_;
}

sge::shader::sampler_sequence const &
sge::shader::object_parameters::samplers() const
{
	return samplers_;
}

sge::shader::object_parameters::~object_parameters()
{
}
