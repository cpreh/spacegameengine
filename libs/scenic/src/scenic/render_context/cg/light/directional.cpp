/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vector4.hpp>
#include <sge/scenic/render_context/cg/light/directional.hpp>
#include <sge/scenic/impl/render_context/cg/any_color_to_vector4.hpp>
#include <fcppt/insert_to_std_string.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/vector/null.hpp>


namespace
{
sge::shader::parameter::name
param_name(
	sge::scenic::render_context::cg::light::index const &_index,
	std::string const &_suffix)
{
	return
		sge::shader::parameter::name(
			"directional_lights["+
			fcppt::insert_to_std_string(
				_index.get())+
			"]."+
			_suffix);
}
}

sge::scenic::render_context::cg::light::directional::directional(
	sge::cg::program::object &_program,
	sge::scenic::render_context::cg::light::index const &_index)
:
	diffuse_color_(
		_program,
		param_name(
			_index,
			"diffuse_color"
		),
		fcppt::math::vector::null<
			sge::renderer::vector4
		>()
	),
	specular_color_(
		_program,
		param_name(
			_index,
			"specular_color"
		),
		fcppt::math::vector::null<
			sge::renderer::vector4
		>()
	),
	ambient_color_(
		_program,
		param_name(
			_index,
			"ambient_color"
		),
		fcppt::math::vector::null<
			sge::renderer::vector4
		>()
	),
	camera_space_direction_(
		_program,
		param_name(
			_index,
			"camera_space_direction"
		),
		fcppt::math::vector::null<
			sge::renderer::vector3
		>()
	)
{
}

void
sge::scenic::render_context::cg::light::directional::diffuse_color(
	sge::scenic::render_context::diffuse_color const &_diffuse_color)
{
	diffuse_color_.set(
		sge::scenic::impl::render_context::cg::any_color_to_vector4(
			_diffuse_color.get()));
}

void
sge::scenic::render_context::cg::light::directional::specular_color(
	sge::scenic::render_context::specular_color const &_specular_color)
{
	specular_color_.set(
		sge::scenic::impl::render_context::cg::any_color_to_vector4(
			_specular_color.get()));
}

void
sge::scenic::render_context::cg::light::directional::ambient_color(
	sge::scenic::render_context::ambient_color const &_ambient_color)
{
	ambient_color_.set(
		sge::scenic::impl::render_context::cg::any_color_to_vector4(
			_ambient_color.get()));
}

void
sge::scenic::render_context::cg::light::directional::camera_space_direction(
	sge::scenic::render_context::light::direction const &_camera_space_direction)
{
	camera_space_direction_.set(
		fcppt::math::vector::normalize(
			_camera_space_direction.get()));
}

sge::scenic::render_context::cg::light::directional::~directional()
{
}
