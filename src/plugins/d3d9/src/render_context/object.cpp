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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/clear.hpp>
#include <sge/d3d9/devicefuncs/draw_indexed_primitive.hpp>
#include <sge/d3d9/devicefuncs/draw_primitive.hpp>
#include <sge/d3d9/devicefuncs/light_enable.hpp>
#include <sge/d3d9/devicefuncs/set_clip_plane.hpp>
#include <sge/d3d9/devicefuncs/set_index_buffer.hpp>
#include <sge/d3d9/devicefuncs/set_light.hpp>
#include <sge/d3d9/devicefuncs/set_material.hpp>
#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/devicefuncs/set_stream_source.hpp>
#include <sge/d3d9/devicefuncs/set_transform.hpp>
#include <sge/d3d9/devicefuncs/set_vertex_declaration.hpp>
#include <sge/d3d9/devicefuncs/texture_stage_arg.hpp>
#include <sge/d3d9/devicefuncs/texture_stage_op.hpp>
#include <sge/d3d9/render_context/object.hpp>
#include <sge/d3d9/state/apply.hpp>
#include <sge/d3d9/target/base.hpp>
#include <sge/d3d9/texture/address_mode.hpp>
#include <sge/d3d9/texture/init_state.hpp>
#include <sge/d3d9/texture/set.hpp>
#include <sge/d3d9/texture/filter/set.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/config.hpp>
#include <sge/renderer/const_optional_vertex_declaration_ref.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/matrix4_fwd.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/glsl/const_optional_program_ref_fwd.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/light/object_fwd.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/list.hpp>
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
#include <fcppt/noncopyable.hpp>

#if defined(SGE_RENDERER_HAVE_CG)
#include <sge/renderer/cg/loaded_program_fwd.hpp>
#endif


sge::d3d9::render_context::object::object(
	IDirect3DDevice9 *const _device,
	sge::renderer::target::base &_target,
	sge::renderer::caps::texture_stages const _texture_stages
)
:
	device_(
		_device
	),
	target_(
		_target
	),
	current_states_(),
	states_(),
	clip_planes_(),
	scoped_target_(
		dynamic_cast<
			sge::d3d9::target::base &
		>(
			target_
		)
	)
{
	this->state(
		sge::renderer::state::default_()
	);

	sge::d3d9::texture::init_state(
		device_,
		_texture_stages
	);
}

sge::d3d9::render_context::object::~object()
{
}

sge::renderer::target::base &
sge::d3d9::render_context::object::target()
{
	return
		target_;
}

void
sge::d3d9::render_context::object::clear(
	sge::renderer::clear::parameters const &_parameters
)
{
	sge::d3d9::devicefuncs::clear(
		device_,
		_parameters
	);
}

void
sge::d3d9::render_context::object::render_indexed(
	sge::renderer::index_buffer const &_index_buffer,
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _num_vertices,
	sge::renderer::indexed_primitive_type::type const _primitive_type,
	sge::renderer::primitive_count const _primitive_count,
	sge::renderer::first_index const _first_index
)
{
	sge::d3d9::devicefuncs::set_index_buffer(
		device_,
		_index_buffer
	);

	sge::d3d9::devicefuncs::draw_indexed_primitive(
		device_,
		_first_vertex,
		_num_vertices,
		_primitive_type,
		_primitive_count,
		_first_index
	);

}

void
sge::d3d9::render_context::object::render_nonindexed(
	sge::renderer::first_vertex const _first_vertex,
	sge::renderer::vertex_count const _num_vertices,
	sge::renderer::nonindexed_primitive_type::type const _primitive_type
)
{
	sge::d3d9::devicefuncs::draw_primitive(
		device_,
		_first_vertex,
		_num_vertices,
		_primitive_type
	);
}

void
sge::d3d9::render_context::object::activate_vertex_buffer(
	sge::renderer::vertex_buffer const &_buffer
)
{
	sge::d3d9::devicefuncs::set_stream_source(
		device_,
		_buffer
	);
}

void
sge::d3d9::render_context::object::deactivate_vertex_buffer(
	sge::renderer::vertex_buffer const &_buffer
)
{
}

void
sge::d3d9::render_context::object::vertex_declaration(
	sge::renderer::const_optional_vertex_declaration_ref const &_declaration
)
{
	if(
		!_declaration
	)
		return;

	sge::d3d9::devicefuncs::set_vertex_declaration(
		device_,
		*_declaration
	);
}

void
sge::d3d9::render_context::object::state(
	sge::renderer::state::list const &_states
)
{
	sge::d3d9::state::apply(
		device_,
		current_states_,
		_states
	);
}

void
sge::d3d9::render_context::object::push_state(
	sge::renderer::state::list const &_states
)
{
	states_.push(
		current_states_
	);

	this->state(
		_states
	);
}

void
sge::d3d9::render_context::object::pop_state()
{
	this->state(
		states_.top()
	);

	states_.pop();
}

void
sge::d3d9::render_context::object::material(
	sge::renderer::material const &_material
)
{
	sge::d3d9::devicefuncs::set_material(
		device_,
		_material
	);
}

void
sge::d3d9::render_context::object::enable_light(
	sge::renderer::light::index const _index,
	bool const _enable
)
{
	sge::d3d9::devicefuncs::light_enable(
		device_,
		_index,
		_enable
	);
}

void
sge::d3d9::render_context::object::light(
	sge::renderer::light::index const _index,
	sge::renderer::light::object const &_light
)
{
	sge::d3d9::devicefuncs::set_light(
		device_,
		_index,
		_light
	);
}

void
sge::d3d9::render_context::object::enable_clip_plane(
	sge::renderer::clip_plane_index const _index,
	bool const _enable
)
{
	clip_planes_.set(
		_index,
		_enable
	);

	sge::d3d9::devicefuncs::set_render_state(
		device_,
		D3DRS_CLIPPLANEENABLE,
		clip_planes_.dword()
	);
}

void
sge::d3d9::render_context::object::clip_plane(
	sge::renderer::clip_plane_index const _index,
	sge::renderer::clip_plane const &_plane
)
{
	sge::d3d9::devicefuncs::set_clip_plane(
		device_,
		_index,
		_plane
	);
}

void
sge::d3d9::render_context::object::texture_stage_op(
	sge::renderer::texture::stage const _stage,
	sge::renderer::texture::stage_op::type const _type,
	sge::renderer::texture::stage_op_value::type const _arg
)
{
	sge::d3d9::devicefuncs::texture_stage_op(
		device_,
		_stage,
		_type,
		_arg
	);
}

void
sge::d3d9::render_context::object::texture_stage_arg(
	sge::renderer::texture::stage const _stage,
	sge::renderer::texture::stage_arg::type const _type,
	sge::renderer::texture::stage_arg_value::type const _arg
)
{
	sge::d3d9::devicefuncs::texture_stage_arg(
		device_,
		_stage,
		_type,
		_arg
	);
}

void
sge::d3d9::render_context::object::texture(
	sge::renderer::texture::const_optional_base_ref const &_texture,
	sge::renderer::texture::stage const _stage
)
{
	sge::d3d9::texture::set(
		device_,
		_stage,
		_texture
	);
}

void
sge::d3d9::render_context::object::texture_filter(
	sge::renderer::texture::filter::object const &_filter,
	sge::renderer::texture::stage const _stage
)
{
	sge::d3d9::texture::filter::set(
		device_,
		_stage,
		_filter
	);
}

void
sge::d3d9::render_context::object::texture_address_mode_s(
	sge::renderer::texture::address_mode_s const _mode,
	sge::renderer::texture::stage const _stage
)
{
	sge::d3d9::texture::address_mode(
		device_,
		_stage,
		_mode
	);
}

void
sge::d3d9::render_context::object::texture_address_mode_t(
	sge::renderer::texture::address_mode_t const _mode,
	sge::renderer::texture::stage const _stage
)
{
	sge::d3d9::texture::address_mode(
		device_,
		_stage,
		_mode
	);
}

void
sge::d3d9::render_context::object::texture_address_mode_u(
	sge::renderer::texture::address_mode_u const _mode,
	sge::renderer::texture::stage const _stage
)
{
	sge::d3d9::texture::address_mode(
		device_,
		_stage,
		_mode
	);
}

void
sge::d3d9::render_context::object::transform(
	sge::renderer::matrix_mode::type const _mode,
	sge::renderer::matrix4 const &_matrix
)
{
	sge::d3d9::devicefuncs::set_transform(
		device_,
		_mode,
		_matrix
	);
}

void
sge::d3d9::render_context::object::glsl_program(
	sge::renderer::glsl::const_optional_program_ref const &_program
)
{
}
