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


#ifndef SGE_RENDERER_DEVICE_HPP_INCLUDED
#define SGE_RENDERER_DEVICE_HPP_INCLUDED

#include <sge/renderer/caps_fwd.hpp>
#include <sge/renderer/clip_plane.hpp>
#include <sge/renderer/clip_plane_index.hpp>
#include <sge/renderer/const_index_buffer_ptr.hpp>
#include <sge/renderer/const_vertex_buffer_ptr.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/first_vertex.hpp>
#include <sge/renderer/index_buffer_ptr.hpp>
#include <sge/renderer/indexed_primitive_type.hpp>
#include <sge/renderer/light_index.hpp>
#include <sge/renderer/light_fwd.hpp>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/onscreen_target_ptr.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/sampler_stage_arg.hpp>
#include <sge/renderer/sampler_stage_arg_value.hpp>
#include <sge/renderer/sampler_stage_op.hpp>
#include <sge/renderer/sampler_stage_op_value.hpp>
#include <sge/renderer/scissor_area.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/target_ptr.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/glsl/const_program_ptr.hpp>
#include <sge/renderer/glsl/optional_istream.hpp>
#include <sge/renderer/glsl/optional_string.hpp>
#include <sge/renderer/glsl/pixel_shader_ptr.hpp>
#include <sge/renderer/glsl/program_ptr.hpp>
#include <sge/renderer/glsl/string.hpp>
#include <sge/renderer/glsl/vertex_shader_ptr.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/texture/const_base_ptr.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <sge/renderer/texture/cube_ptr.hpp>
#include <sge/renderer/texture/depth_stencil_ptr.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_ptr.hpp>
#include <sge/renderer/vf/dynamic/const_view_fwd.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>
#include <sge/window/instance_ptr.hpp>
#include <sge/class_symbol.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL device
{
	FCPPT_NONCOPYABLE(
		device
	);
protected:
	SGE_SYMBOL device();
public:
	virtual void
	begin_rendering() = 0;

	virtual void
	end_rendering() = 0;

	virtual void
	render(
		const_index_buffer_ptr,
		first_vertex,
		vertex_count,
		indexed_primitive_type::type ptype,
		primitive_count,
		first_index
	) = 0;

	virtual void
	render(
		first_vertex,
		vertex_count,
		nonindexed_primitive_type::type ptype
	) = 0;

	virtual void
	set_vertex_buffer(
		const_vertex_buffer_ptr
	) = 0;

	virtual void
	unset_vertex_buffer(
		const_vertex_buffer_ptr
	) = 0;

	virtual void
	state(
		renderer::state::list const &
	) = 0;

	virtual void
	push_state(
		renderer::state::list const &
	) = 0;

	virtual void
	pop_state() = 0;

	virtual void
	material(
		renderer::material const &
	) = 0;

	virtual void
	enable_light(
		light_index,
		bool enable
	) = 0;

	virtual void
	light(
		light_index,
		renderer::light const &
	) = 0;

	virtual void
	enable_clip_plane(
		clip_plane_index,
		bool enable
	) = 0;

	virtual void
	clip_plane(
		clip_plane_index,
		renderer::clip_plane const &
	) = 0;

	virtual void
	scissor_area(
		renderer::scissor_area const &
	) = 0;

	virtual void
	sampler_stage_op(
		stage_type,
		renderer::sampler_stage_op::type,
		renderer::sampler_stage_op_value::type
	) = 0;

	virtual void
	sampler_stage_arg(
		stage_type,
		renderer::sampler_stage_arg::type,
		renderer::sampler_stage_arg_value::type
	) = 0;

	virtual void
	texture(
		texture::const_base_ptr,
		stage_type
	) = 0;

	virtual void
	transform(
		matrix_mode::type,
		matrix4 const &
	) = 0;

	virtual void
	target(
		renderer::target_ptr
	) = 0;

	SGE_SYMBOL
	glsl::program_ptr const
	create_glsl_program(
		glsl::optional_string const &vertex_shader_source,
		glsl::optional_string const &pixel_shader_source
	);

	SGE_SYMBOL
	glsl::program_ptr const
	create_glsl_program(
		glsl::optional_istream const &vertex_shader_source,
		glsl::optional_istream const &pixel_shader_source
	);

	virtual glsl::program_ptr const
	create_glsl_program() = 0;

	virtual glsl::vertex_shader_ptr const
	create_glsl_vertex_shader(
		glsl::string const &
	) = 0;

	virtual glsl::pixel_shader_ptr const
	create_glsl_pixel_shader(
		glsl::string const &
	) = 0;

	virtual void
	glsl_program(
		renderer::glsl::const_program_ptr
	) = 0;

	virtual renderer::target_ptr const
	create_target() = 0;

	virtual renderer::texture::planar_ptr const
	create_planar_texture(
		renderer::texture::planar_parameters const &
	) = 0;

	virtual renderer::texture::depth_stencil_ptr const
	create_depth_stencil_texture(
		renderer::dim2 const &,
		renderer::depth_stencil_format::type
	) = 0;

	virtual renderer::depth_stencil_surface_ptr const
	create_depth_stencil_surface(
		renderer::dim2 const &,
		renderer::depth_stencil_format::type
	) = 0;

	virtual renderer::texture::volume_ptr const
	create_volume_texture(
		renderer::texture::volume_parameters const &
	) = 0;

	virtual renderer::texture::cube_ptr const
	create_cube_texture(
		renderer::texture::cube_parameters const &
	) = 0;

	SGE_SYMBOL vertex_buffer_ptr const
	create_vertex_buffer(
		vf::dynamic::const_view const &,
		resource_flags_field const &
	);

	virtual vertex_buffer_ptr const
	create_vertex_buffer(
		vf::dynamic::format const &,
		size_type size,
		resource_flags_field const &
	) = 0;

	SGE_SYMBOL index_buffer_ptr const
	create_index_buffer(
		index::dynamic::const_view const &,
		resource_flags_field const &
	);

	virtual index_buffer_ptr const
	create_index_buffer(
		index::dynamic::format::type,
		size_type size,
		resource_flags_field const &
	) = 0;

	virtual renderer::onscreen_target_ptr const
	onscreen_target() const = 0;

	virtual renderer::scissor_area const
	scissor_area() const = 0;

	virtual renderer::target_ptr const
	target() const = 0;

	virtual renderer::matrix4 const
	transform(
		renderer::matrix_mode::type
	) = 0;

	virtual renderer::caps const
	caps() const = 0;

	virtual renderer::screen_size const
	screen_size() const = 0;

	virtual sge::window::instance_ptr const
	window() const = 0;

	SGE_SYMBOL virtual ~device();
};

}
}

#endif
