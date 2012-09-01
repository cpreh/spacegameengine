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


#include <sge/scenic/render_context/cg/manager.hpp>
#include <sge/scenic/render_context/cg/object.hpp>
#include <sge/scenic/index_buffer_range.hpp>
#include <fcppt/math/matrix/arithmetic.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/context/object.hpp>
#include <fcppt/math/matrix/inverse.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/cull_mode.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/state/bool.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <sge/renderer/texture/filter/mipmap.hpp>

#include <iostream>

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
}

void
sge::scenic::render_context::cg::object::diffuse_texture(
	sge::scenic::render_context::optional_planar_texture const &_texture)
{
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
	sge::scenic::render_context::light_sequence const &)
{
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
