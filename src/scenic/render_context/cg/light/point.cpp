/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/any/object.hpp>
#include <sge/renderer/vector4.hpp>
#include <sge/scenic/render_context/cg/light/point.hpp>
#include <sge/scenic/render_context/light/attenuation.hpp>
#include <sge/src/scenic/render_context/cg/any_color_to_vector4.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace
{
sge::shader::parameter::name const
param_name(
	sge::scenic::render_context::cg::light::index const &_index,
	std::string const &_suffix)
{
	return
		sge::shader::parameter::name(
			"point_lights["+
			fcppt::insert_to_std_string(
				_index.get())+
			"]."+
			_suffix);
}
}

sge::scenic::render_context::cg::light::point::point(
	sge::cg::program::object &_program,
	sge::scenic::render_context::cg::light::index const &_index)
:
	diffuse_color_(
		_program,
		param_name(
			_index,
			"diffuse_color"),
		sge::renderer::vector4()),
	specular_color_(
		_program,
		param_name(
			_index,
			"specular_color"),
		sge::renderer::vector4()),
	ambient_color_(
		_program,
		param_name(
			_index,
			"ambient_color"),
		sge::renderer::vector4()),
	camera_space_position_(
		_program,
		param_name(
			_index,
			"camera_space_position"),
		sge::renderer::vector3()),
	attenuation_(
		_program,
		param_name(
			_index,
			"attenuation"),
		sge::renderer::vector3())
{
}

void
sge::scenic::render_context::cg::light::point::diffuse_color(
	sge::scenic::render_context::diffuse_color const &_diffuse_color)
{
	diffuse_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_diffuse_color.get()));
}

void
sge::scenic::render_context::cg::light::point::specular_color(
	sge::scenic::render_context::specular_color const &_specular_color)
{
	specular_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_specular_color.get()));
}

void
sge::scenic::render_context::cg::light::point::ambient_color(
	sge::scenic::render_context::ambient_color const &_ambient_color)
{
	ambient_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_ambient_color.get()));
}

void
sge::scenic::render_context::cg::light::point::camera_space_position(
	sge::renderer::vector3 const &_camera_space_position)
{
	camera_space_position_.set(
		_camera_space_position);
}

void
sge::scenic::render_context::cg::light::point::attenuation(
	sge::scenic::render_context::light::attenuation const &_attenuation)
{
	attenuation_.set(
		sge::renderer::vector3(
			_attenuation.constant_attenuation().get(),
			_attenuation.linear_attenuation().get(),
			_attenuation.quadratic_attenuation().get()));
}

sge::scenic::render_context::cg::light::point::~point()
{
}
