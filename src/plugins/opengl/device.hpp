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

#include "device_state_fwd.hpp"
#include "onscreen_target_fwd.hpp"
#include "target_base_fwd.hpp"
#include "context/object.hpp"
#include "fbo/target_fwd.hpp"
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/caps_fwd.hpp>
#include <sge/renderer/clear_flags_field.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/const_optional_vertex_declaration_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/onscreen_target_fwd.hpp>
#include <sge/renderer/optional_target_fwd.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/target_ptr.hpp>
#include <sge/renderer/sampler_stage_arg.hpp>
#include <sge/renderer/sampler_stage_arg_value.hpp>
#include <sge/renderer/sampler_stage_op.hpp>
#include <sge/renderer/sampler_stage_op_value.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/renderer/glsl/const_optional_program_fwd.hpp>
#include <sge/renderer/glsl/geometry_shader_ptr.hpp>
#include <sge/renderer/glsl/pixel_shader_ptr.hpp>
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/vertex_shader_ptr.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/light/index.hpp>
#include <sge/renderer/light/object_fwd.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/stack.hpp>
#include <sge/renderer/texture/const_optional_base_fwd.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_ptr.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_ptr.hpp>
#include <sge/renderer/texture/filter/object_fwd.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/window/instance_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

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
		window::instance &
	);

	~device();

	void
	begin_rendering();

	void
	end_rendering();

	void
	clear(
		renderer::clear_flags_field const &
	);

	void
	render_indexed(
		renderer::index_buffer const &,
		renderer::first_vertex,
		renderer::vertex_count,
		renderer::indexed_primitive_type::type,
		renderer::primitive_count,
		renderer::first_index
	);

	void
	render_nonindexed(
		renderer::first_vertex,
		renderer::vertex_count,
		renderer::nonindexed_primitive_type::type
	);

	void
	activate_vertex_buffer(
		renderer::vertex_buffer const &
	);

	void
	deactivate_vertex_buffer(
		renderer::vertex_buffer const &
	);

	void
	vertex_declaration(
		renderer::const_optional_vertex_declaration const &
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
		renderer::light::index,
		bool enable
	);

	void
	light(
		renderer::light::index,
		renderer::light::object const &
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
	sampler_stage_op(
		renderer::stage stage,
		renderer::sampler_stage_op::type,
		renderer::sampler_stage_op_value::type
	);

	void
	sampler_stage_arg(
		renderer::stage stage,
		renderer::sampler_stage_arg::type,
		renderer::sampler_stage_arg_value::type
	);

	void
	texture_filter(
		renderer::texture::filter::object const &,
		renderer::stage
	);

	void
	texture(
		renderer::texture::const_optional_base const &,
		renderer::stage
	);

	void
	transform(
		renderer::matrix_mode::type,
		renderer::matrix4 const &
	);

	void
	target(
		renderer::optional_target const &
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

	renderer::glsl::geometry_shader_ptr const
	create_glsl_geometry_shader(
		renderer::glsl::string const &
	);

	void
	glsl_program(
		renderer::glsl::const_optional_program const &
	);

	renderer::target_ptr const
	create_target();

	renderer::texture::planar_ptr const
	create_planar_texture(
		renderer::texture::planar_parameters const &
	);

	renderer::texture::depth_stencil_ptr const
	create_depth_stencil_texture(
		renderer::texture::depth_stencil_parameters const &
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
		renderer::vertex_declaration const &,
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

	renderer::onscreen_target &
	onscreen_target() const;

	renderer::optional_target const
	target() const;

	renderer::caps const
	caps() const;

	window::instance &
	window() const;
private:
	bool
	fbo_active() const;

	renderer::depth_stencil_buffer::type const depth_stencil_buffer_;

	window::instance &window_;

	renderer::state::list current_states_;

	mutable opengl::context::object context_;

	typedef fcppt::scoped_ptr<
		opengl::device_state
	> device_state_scoped_ptr;

	device_state_scoped_ptr state_;

	typedef fcppt::scoped_ptr<
		opengl::onscreen_target
	> onscreen_target_scoped_ptr;

	onscreen_target_scoped_ptr const onscreen_target_;

	opengl::fbo::target *fbo_target_;

	opengl::target_base *target_;

	mutable fcppt::scoped_ptr<
		renderer::caps
	> caps_;

	sge::renderer::state::stack state_levels_;
};

}
}

#endif
