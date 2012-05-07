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


#include <sge/opengl/draw_arrays.hpp>
#include <sge/opengl/draw_elements.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/set_clip_plane.hpp>
#include <sge/opengl/set_material.hpp>
#include <sge/opengl/set_matrix_and_mode.hpp>
#include <sge/opengl/set_vertex_buffer.hpp>
#include <sge/opengl/set_vertex_declaration.hpp>
#include <sge/opengl/target_base.hpp>
#include <sge/opengl/unset_vertex_buffer.hpp>
#include <sge/opengl/clear/set.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/convert/clip_plane_index.hpp>
#include <sge/opengl/light/enable.hpp>
#include <sge/opengl/light/set.hpp>
#include <sge/opengl/render_context/object.hpp>
#include <sge/opengl/state/apply.hpp>
#include <sge/opengl/state/initial.hpp>
#include <sge/opengl/texture/activate.hpp>
#include <sge/opengl/texture/set_stage_funcs.hpp>
#include <sge/opengl/texture/address_mode/update.hpp>
#include <sge/opengl/texture/filter/update.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/const_optional_vertex_declaration_ref_fwd.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/light/object_fwd.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>
#include <sge/renderer/texture/const_optional_base_ref_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/stage_arg.hpp>
#include <sge/renderer/texture/stage_arg_value.hpp>
#include <sge/renderer/texture/stage_op.hpp>
#include <sge/renderer/texture/stage_op_value.hpp>
#include <sge/renderer/texture/filter/object_fwd.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/opengl/cg/program/activate.hpp>
#include <sge/opengl/cg/program/deactivate.hpp>
#include <sge/opengl/cg/texture/enable.hpp>
#include <sge/opengl/cg/texture/disable.hpp>
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#include <sge/renderer/cg/loaded_texture_fwd.hpp>
#endif


sge::opengl::render_context::object::object(
	sge::opengl::context::object &_context,
	sge::renderer::target::base &_target,
	sge::renderer::depth_stencil_buffer::type const _depth_stencil_buffer
)
:
	context_(
		_context
	),
	depth_stencil_buffer_(
		_depth_stencil_buffer
	),
	target_(
		_target
	),
	current_states_(
		sge::opengl::state::initial()
	),
	state_levels_(),
	scoped_target_(
		dynamic_cast<
			sge::opengl::target_base &
		>(
			target_
		)
	)
{
	this->state(
		sge::renderer::state::default_()
	);
}

sge::opengl::render_context::object::~object()
{
}

void
sge::opengl::render_context::object::end_rendering()
{
	scoped_target_.target().end_rendering();
}

sge::renderer::target::base &
sge::opengl::render_context::object::target()
{
	return
		target_;
}

void
sge::opengl::render_context::object::clear(
	sge::renderer::clear::parameters const &_parameters
)
{
	sge::opengl::clear::set(
		_parameters
	);
}

void
sge::opengl::render_context::object::render_indexed(
	sge::renderer::index_buffer const &_ib,
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _num_vertices,
	sge::renderer::indexed_primitive_type::type const _ptype,
	sge::renderer::primitive_count const _pcount,
	sge::renderer::first_index const _first_index
)
{
	sge::opengl::draw_elements(
		context_,
		_ib,
		_first_vertex,
		_num_vertices,
		_ptype,
		_pcount,
		_first_index
	);
}

void
sge::opengl::render_context::object::render_nonindexed(
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _num_vertices,
	sge::renderer::nonindexed_primitive_type::type const _ptype
)
{
	sge::opengl::draw_arrays(
		_first_vertex,
		_num_vertices,
		_ptype
	);
}

void
sge::opengl::render_context::object::activate_vertex_buffer(
	sge::renderer::vertex_buffer const &_vertex_buffer
)
{
	sge::opengl::set_vertex_buffer(
		context_,
		_vertex_buffer
	);
}

void
sge::opengl::render_context::object::deactivate_vertex_buffer(
	sge::renderer::vertex_buffer const &_vertex_buffer
)
{
	sge::opengl::unset_vertex_buffer(
		context_,
		_vertex_buffer
	);
}

void
sge::opengl::render_context::object::vertex_declaration(
	sge::renderer::const_optional_vertex_declaration_ref const &_vertex_declaration
)
{
	sge::opengl::set_vertex_declaration(
		context_,
		_vertex_declaration
	);
}

void
sge::opengl::render_context::object::state(
	sge::renderer::state::list const &_states
)
{
	sge::opengl::state::apply(
		context_,
		current_states_,
		_states,
		depth_stencil_buffer_
	);
}

void
sge::opengl::render_context::object::push_state(
	sge::renderer::state::list const &_states
)
{
	state_levels_.push(
		current_states_
	);

	this->state(
		_states
	);
}

void
sge::opengl::render_context::object::pop_state()
{
	this->state(
		state_levels_.top()
	);

	state_levels_.pop();
}

void
sge::opengl::render_context::object::material(
	sge::renderer::material const &_mat
)
{
	sge::opengl::set_material(
		_mat
	);
}

void
sge::opengl::render_context::object::enable_light(
	sge::renderer::light::index const _index,
	bool const _enable
)
{
	sge::opengl::light::enable(
		_index,
		_enable
	);
}

void
sge::opengl::render_context::object::light(
	sge::renderer::light::index const _index,
	sge::renderer::light::object const &_light
)
{
	sge::opengl::light::set(
		_index,
		_light
	);
}

void
sge::opengl::render_context::object::enable_clip_plane(
	sge::renderer::clip_plane_index const _index,
	bool const _enable
)
{
	sge::opengl::enable_bool(
		sge::opengl::convert::clip_plane_index(
			_index
		),
		_enable
	);
}

void
sge::opengl::render_context::object::clip_plane(
	sge::renderer::clip_plane_index const _index,
	sge::renderer::clip_plane const &_clip_plane
)
{
	sge::opengl::set_clip_plane(
		_index,
		_clip_plane
	);
}

void
sge::opengl::render_context::object::texture_stage_op(
	sge::renderer::texture::stage const _stage,
	sge::renderer::texture::stage_op::type const _op,
	sge::renderer::texture::stage_op_value::type const _value
)
{
	sge::opengl::texture::set_stage_funcs(
		context_,
		_stage,
		_op,
		_value
	);
}

void
sge::opengl::render_context::object::texture_stage_arg(
	sge::renderer::texture::stage const _stage,
	sge::renderer::texture::stage_arg::type const _arg,
	sge::renderer::texture::stage_arg_value::type const _value
)
{
	sge::opengl::texture::set_stage_funcs(
		context_,
		_stage,
		_arg,
		_value
	);
}

void
sge::opengl::render_context::object::texture_filter(
	sge::renderer::texture::filter::object const &_filter,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::filter::update(
		context_,
		_stage,
		_filter
	);
}

void
sge::opengl::render_context::object::texture_address_mode_s(
	sge::renderer::texture::address_mode_s const _mode,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::address_mode::update(
		context_,
		_mode,
		_stage
	);
}

void
sge::opengl::render_context::object::texture_address_mode_t(
	sge::renderer::texture::address_mode_t const _mode,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::address_mode::update(
		context_,
		_mode,
		_stage
	);
}

void
sge::opengl::render_context::object::texture_address_mode_u(
	sge::renderer::texture::address_mode_u const _mode,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::address_mode::update(
		context_,
		_mode,
		_stage
	);
}

void
sge::opengl::render_context::object::texture(
	sge::renderer::texture::const_optional_base_ref const &_texture,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::activate(
		context_,
		_texture,
		_stage
	);
}

void
sge::opengl::render_context::object::transform(
	sge::renderer::matrix_mode::type const _mode,
	sge::renderer::matrix4 const &_matrix
)
{
	sge::opengl::set_matrix_and_mode(
		context_,
		_mode,
		_matrix
	);
}

#if defined(SGE_RENDERER_HAVE_CG)
void
sge::opengl::render_context::object::set_cg_program(
	sge::renderer::cg::loaded_program const &_program
)
{
	sge::opengl::cg::program::activate(
		_program
	);
}

void
sge::opengl::render_context::object::unset_cg_program(
	sge::renderer::cg::loaded_program const &_program
)
{
	sge::opengl::cg::program::deactivate(
		_program
	);
}

sge::renderer::texture::stage const
sge::opengl::render_context::object::set_cg_texture(
	sge::renderer::cg::loaded_texture const &_texture
)
{
	return
		sge::opengl::cg::texture::enable(
			_texture
		);
}

void
sge::opengl::render_context::object::unset_cg_texture(
	sge::renderer::cg::loaded_texture const &_texture
)
{
	sge::opengl::cg::texture::disable(
		_texture
	);
}
#endif
