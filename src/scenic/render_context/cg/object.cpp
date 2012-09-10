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


#include <sge/renderer/material.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/light/point.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/texture/filter/mipmap.hpp>
#include <sge/scenic/index_buffer_range.hpp>
#include <sge/scenic/render_context/cg/manager.hpp>
#include <sge/scenic/render_context/cg/object.hpp>
#include <sge/scenic/render_context/cg/point_light.hpp>
#include <sge/src/scenic/render_context/cg/any_color_to_vector4.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <fcppt/math/matrix/inverse.hpp>
#include <fcppt/math/matrix/multiply_matrix4_vector3.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iostream>
#include <fcppt/config/external_end.hpp>


sge::scenic::render_context::cg::object::object(
	sge::scenic::render_context::cg::manager &_manager,
	sge::renderer::context::object &_context)
:
	sge::scenic::render_context::base(),
	manager_(
		_manager),
	context_(
		_context),
	scoped_vd_(
		_context,
		_manager.vertex_declaration_),
	scoped_state_(
		_context,
		sge::renderer::state::list
			(sge::renderer::state::depth_func::less)
			(sge::renderer::state::bool_::enable_alpha_blending = false)
			(sge::renderer::state::cull_mode::counter_clockwise)),
	scoped_texture_filter_(
		_context,
		sge::renderer::texture::stage(
			0u),
		sge::renderer::texture::filter::mipmap()),
	scoped_shader_(
		_context,
		manager_.shader_),
	current_world_(),
	current_projection_(),
	current_vertex_buffer_()
{
}

void
sge::scenic::render_context::cg::object::transform(
	sge::renderer::matrix_mode::type const _matrix_mode,
	sge::renderer::matrix4 const &_matrix)
{
	switch(_matrix_mode)
	{
	case sge::renderer::matrix_mode::world:
		current_world_ =
			_matrix;

		manager_.world_matrix_.set(
			current_world_);

		manager_.world_inverse_transpose_matrix_.set(
			fcppt::math::matrix::inverse(
				fcppt::math::matrix::transpose(
					current_world_)));

		manager_.world_projection_matrix_.set(
			current_projection_ * current_world_);
		break;
	case sge::renderer::matrix_mode::projection:
		current_projection_ =
			_matrix;

		manager_.world_projection_matrix_.set(
			current_projection_ * current_world_);
		break;
	case sge::renderer::matrix_mode::size:
		break;
	}
}

void
sge::scenic::render_context::cg::object::material(
	sge::renderer::material const &_material)
{
	manager_.material_diffuse_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_material.diffuse().get()));

	manager_.material_specular_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_material.specular().get()));

	manager_.material_emissive_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_material.emissive().get()));

	manager_.material_ambient_color_.set(
		sge::scenic::render_context::cg::any_color_to_vector4(
			_material.ambient().get()));

	manager_.material_shininess_.set(
		_material.shininess().get());
}

void
sge::scenic::render_context::cg::object::diffuse_texture(
	sge::scenic::render_context::optional_planar_texture const &_texture)
{
	manager_.use_diffuse_texture_.set(
		_texture.has_value());

	manager_.diffuse_texture_.set(
		_texture
		?
			sge::shader::parameter::planar_texture::optional_value(
				*_texture)
		:
			sge::shader::parameter::planar_texture::optional_value());
}

void
sge::scenic::render_context::cg::object::lights(
	sge::scenic::render_context::light_sequence const &_lights)
{
	manager_.point_light_count_.set(
		static_cast<int>(
			_lights.size()));

	std::size_t current_index =
		0u;

	for(
		sge::scenic::render_context::light_sequence::const_iterator l =
			_lights.begin();
		l != _lights.end();
		++l)
	{
		sge::scenic::render_context::cg::point_light &current_light(
			manager_.point_lights_[current_index]);

		current_light.diffuse_color(
			l->diffuse());

		current_light.specular_color(
			l->specular());

		current_light.ambient_color(
			l->ambient());

		sge::renderer::light::point const &point_light(
			l->variant().get<sge::renderer::light::point>());

		current_light.camera_space_position(
			fcppt::math::matrix::multiply_matrix4_vector3(
				current_world_,
				point_light.position().get()));

		current_light.attenuation(
			point_light.attenuation());

		++current_index;
	}
}

void
sge::scenic::render_context::cg::object::vertex_buffer(
	sge::renderer::vertex_buffer const &_vertex_buffer)
{
	if(current_vertex_buffer_)
		context_.deactivate_vertex_buffer(
			*current_vertex_buffer_);

	current_vertex_buffer_ =
		optional_vertex_buffer(
			_vertex_buffer);

	context_.activate_vertex_buffer(
		*current_vertex_buffer_);
}

void
sge::scenic::render_context::cg::object::render(
	sge::renderer::index_buffer const &_index_buffer,
	sge::scenic::index_buffer_range const &_index_buffer_range)
{
	context_.render_indexed(
		_index_buffer,
		sge::renderer::first_vertex(
			0u),
		sge::renderer::vertex_count(
			current_vertex_buffer_->size()),
		sge::renderer::primitive_type::triangle_list,
		_index_buffer_range.first_index(),
		_index_buffer_range.index_count());
}

sge::renderer::target::base &
sge::scenic::render_context::cg::object::target()
{
	return
		context_.target();
}

sge::scenic::render_context::cg::object::~object()
{
	if(current_vertex_buffer_)
		context_.deactivate_vertex_buffer(
			*current_vertex_buffer_);
}
