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
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/text.hpp>

sge::shader::object_parameters::object_parameters(
	renderer::device &_renderer,
	renderer::vertex_declaration const &_vertex_declaration,
	shader::vertex_format_string const &_vertex_format_string,
	shader::variable_sequence const &_variables,
	shader::sampler_sequence const &_samplers)
:
	renderer_(
		_renderer),
	vertex_declaration_(
		_vertex_declaration),
	vertex_shaders_(),
	fragment_shaders_(),
	vertex_format_string_(
		_vertex_format_string),
	variables_(
		_variables),
	samplers_(
		_samplers),
	name_(
		FCPPT_TEXT("unnamed"))
{
}

sge::shader::object_parameters &
sge::shader::object_parameters::vertex_shader(
	std::string const &s)
{
	vertex_shaders_.push_back(
		s);
	return *this;
}

sge::shader::object_parameters &
sge::shader::object_parameters::vertex_shader(
	fcppt::filesystem::path const &f)
{
	vertex_shaders_.push_back(
		fcppt::io::stream_to_string(
			*fcppt::make_unique_ptr<fcppt::io::cifstream>(
				f)));
	return *this;
}

sge::shader::object_parameters &
sge::shader::object_parameters::fragment_shader(
	std::string const &s)
{
	fragment_shaders_.push_back(
		s);
	return *this;
}

sge::shader::object_parameters &
sge::shader::object_parameters::fragment_shader(
	fcppt::filesystem::path const &f)
{
	fragment_shaders_.push_back(
		fcppt::io::stream_to_string(
			*fcppt::make_unique_ptr<fcppt::io::cifstream>(
				f)));
	return *this;
}

sge::shader::object_parameters &
sge::shader::object_parameters::name(
	fcppt::string const &_name)
{
	name_ = 
		_name;
	return *this;
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

sge::shader::object_parameters::shader_sequence const &
sge::shader::object_parameters::vertex_shaders() const
{
	return vertex_shaders_;
}

sge::shader::object_parameters::shader_sequence const &
sge::shader::object_parameters::fragment_shaders() const
{
	return fragment_shaders_;
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

fcppt::string const &
sge::shader::object_parameters::name() const
{
	return name_;
}

sge::shader::object_parameters::~object_parameters()
{
}
