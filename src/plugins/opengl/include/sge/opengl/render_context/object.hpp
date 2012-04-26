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


#ifndef SGE_OPENGL_RENDER_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_RENDER_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/render_context/scoped_target.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/const_optional_vertex_declaration_ref_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
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
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/glsl/const_optional_program_ref_fwd.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/light/object_fwd.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/stack.hpp>
#include <sge/renderer/target/base_fwd.hpp>
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


namespace sge
{
namespace opengl
{
namespace render_context
{

class object
:
	public sge::renderer::context::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::opengl::context::object &,
		sge::renderer::target::base &,
		sge::renderer::depth_stencil_buffer::type
	);

	~object();

	void
	end_rendering();
private:
	sge::renderer::target::base &
	target();

	void
	clear(
		sge::renderer::clear::parameters const &
	);

	void
	render_indexed(
		sge::renderer::index_buffer const &,
		sge::renderer::first_vertex,
		sge::renderer::vertex_count,
		sge::renderer::indexed_primitive_type::type,
		sge::renderer::primitive_count,
		sge::renderer::first_index
	);

	void
	render_nonindexed(
		sge::renderer::first_vertex,
		sge::renderer::vertex_count,
		sge::renderer::nonindexed_primitive_type::type
	);

	void
	activate_vertex_buffer(
		sge::renderer::vertex_buffer const &
	);

	void
	deactivate_vertex_buffer(
		sge::renderer::vertex_buffer const &
	);

	void
	vertex_declaration(
		sge::renderer::const_optional_vertex_declaration_ref const &
	);

	void
	state(
		sge::renderer::state::list const &
	);

	void
	push_state(
		sge::renderer::state::list const &
	);

	void
	pop_state();

	void
	material(
		sge::renderer::material const &
	);

	void
	enable_light(
		sge::renderer::light::index,
		bool enable
	);

	void
	light(
		sge::renderer::light::index,
		sge::renderer::light::object const &
	);

	void
	enable_clip_plane(
		sge::renderer::clip_plane_index,
		bool enable
	);

	void
	clip_plane(
		sge::renderer::clip_plane_index,
		sge::renderer::clip_plane const &
	);

	void
	texture_stage_op(
		sge::renderer::texture::stage,
		sge::renderer::texture::stage_op::type,
		sge::renderer::texture::stage_op_value::type
	);

	void
	texture_stage_arg(
		sge::renderer::texture::stage,
		sge::renderer::texture::stage_arg::type,
		sge::renderer::texture::stage_arg_value::type
	);

	void
	texture_filter(
		sge::renderer::texture::filter::object const &,
		sge::renderer::texture::stage
	);

	void
	texture_address_mode_s(
		sge::renderer::texture::address_mode_s,
		sge::renderer::texture::stage
	);

	void
	texture_address_mode_t(
		sge::renderer::texture::address_mode_t,
		sge::renderer::texture::stage
	);

	void
	texture_address_mode_u(
		sge::renderer::texture::address_mode_u,
		sge::renderer::texture::stage
	);

	void
	texture(
		sge::renderer::texture::const_optional_base_ref const &,
		sge::renderer::texture::stage
	);

	void
	transform(
		sge::renderer::matrix_mode::type,
		sge::renderer::matrix4 const &
	);

	void
	glsl_program(
		sge::renderer::glsl::const_optional_program_ref const &
	);

	sge::opengl::context::object &context_;

	sge::renderer::depth_stencil_buffer::type const depth_stencil_buffer_;

	sge::renderer::target::base &target_;

	sge::renderer::state::list current_states_;

	sge::renderer::state::stack state_levels_;

	sge::opengl::render_context::scoped_target const scoped_target_;
};

}
}
}

#endif
