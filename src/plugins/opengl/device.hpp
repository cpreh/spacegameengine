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


#ifndef SGE_OPENGL_DEVICE_HPP_INCLUDED
#define SGE_OPENGL_DEVICE_HPP_INCLUDED

#include "common.hpp"
#include "device_state_ptr.hpp"
#include "onscreen_target_ptr.hpp"
#include "target_base_ptr.hpp"
#include "context/object.hpp"
#include "fbo/target_ptr.hpp"
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/window/instance_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <stack>

namespace sge
{
namespace opengl
{

class device
:
	public renderer::device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		renderer::parameters const &,
		renderer::adapter,
		window::instance_ptr
	);

	~device();

	void
	begin_rendering();

	void
	end_rendering();

	void
	render(
		renderer::const_index_buffer_ptr,
		renderer::first_vertex,
		renderer::vertex_count,
		renderer::indexed_primitive_type::type,
		renderer::primitive_count,
		renderer::first_index
	);

	void
	render(
		renderer::first_vertex,
		renderer::vertex_count,
		renderer::nonindexed_primitive_type::type 
	);

	void
	vertex_buffer(
		renderer::vf::dynamic::part_index,
		renderer::const_vertex_buffer_ptr
	);

	void
	vertex_declaration(
		renderer::const_vertex_declaration_ptr
	);

	void
	state(
		renderer::state::list const &
	);

	void
	push_state(
		renderer::state::list const &
	);

	void
	pop_state();

	void
	material(
		renderer::material const &
	);

	void
	enable_light(
		renderer::light_index,
		bool enable
	);

	void
	light(
		renderer::light_index,
		renderer::light const &
	);

	void
	enable_clip_plane(
		renderer::clip_plane_index,
		bool enable
	);

	void
	clip_plane(
		renderer::clip_plane_index,
		renderer::clip_plane const &
	);

	void
	scissor_area(
		renderer::scissor_area const &
	);

	void
	sampler_stage_op(
		renderer::stage_type stage,
		renderer::sampler_stage_op::type,
		renderer::sampler_stage_op_value::type
	);

	void
	sampler_stage_arg(
		renderer::stage_type stage,
		renderer::sampler_stage_arg::type,
		renderer::sampler_stage_arg_value::type
	);

	void
	texture(
		renderer::texture::const_base_ptr,
		renderer::stage_type
	);

	void
	transform(
		renderer::matrix_mode::type,
		renderer::matrix4 const &
	);

	void
	target(
		renderer::target_ptr
	);

	renderer::glsl::program_ptr const
	create_glsl_program();

	renderer::glsl::vertex_shader_ptr const
	create_glsl_vertex_shader(
		renderer::glsl::string const &
	);

	renderer::glsl::pixel_shader_ptr const
	create_glsl_pixel_shader(
		renderer::glsl::string const &
	);

	void
	glsl_program(
		renderer::glsl::const_program_ptr
	);

	renderer::target_ptr const
	create_target();

	renderer::texture::planar_ptr const
	create_planar_texture(
		renderer::texture::planar_parameters const &
	);

	renderer::texture::depth_stencil_ptr const
	create_depth_stencil_texture(
		renderer::dim2 const &,
		renderer::depth_stencil_format::type
	);

	renderer::depth_stencil_surface_ptr const
	create_depth_stencil_surface(
		renderer::dim2 const &,
		renderer::depth_stencil_format::type
	);

	renderer::texture::volume_ptr const
	create_volume_texture(
		renderer::texture::volume_parameters const &
	);

	renderer::texture::cube_ptr const
	create_cube_texture(
		renderer::texture::cube_parameters const &
	);

	renderer::vertex_declaration_ptr const
	create_vertex_declaration(
		renderer::vf::dynamic::format const &
	);

	renderer::vertex_buffer_ptr const
	create_vertex_buffer(
		renderer::vertex_declaration_ptr,
		renderer::vf::dynamic::part_index,
		renderer::size_type,
		renderer::resource_flags_field const &
	);

	renderer::index_buffer_ptr const
	create_index_buffer(
		renderer::index::dynamic::format::type,
		renderer::size_type,
		renderer::resource_flags_field const &
	);

	renderer::onscreen_target_ptr const
	onscreen_target() const;

	renderer::scissor_area const
	scissor_area() const;

	renderer::target_ptr const
	target() const;

	renderer::matrix4 const
	transform(
		renderer::matrix_mode::type
	);

	renderer::caps const
	caps() const;

	window::instance_ptr const
	window() const;
private:
	GLenum
	clear_bit(
		renderer::state::bool_::trampoline_type const &
	) const;

	bool
	fbo_active() const;

	renderer::depth_stencil_buffer::type const depth_stencil_buffer_;

	window::instance_ptr const window_;

	renderer::state::list current_states_;

	opengl::device_state_ptr state_;

	opengl::onscreen_target_ptr const onscreen_target_;

	opengl::fbo::target_ptr fbo_target_;

	opengl::target_base_ptr target_;

	typedef std::stack<
		renderer::state::list
	> stack_type;

	mutable fcppt::scoped_ptr<
		renderer::caps
	> caps_;

	stack_type state_levels_;

	mutable context::object context_;
};

}
}

#endif
