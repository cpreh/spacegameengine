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


#ifndef SGE_D3D9_DEVICE_HPP_INCLUDED
#define SGE_D3D9_DEVICE_HPP_INCLUDED

#include "d3d_ptr.hpp"
#include "resource_list.hpp"
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/window/instance_ptr.hpp>

namespace sge
{
namespace d3d9
{

class device
:
	public sge::renderer::device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		d3d9::d3d_ptr,
		renderer::adapter,
		renderer::parameters const &,
		window::instance_ptr
	);

	~device();

	void
	begin_rendering();

	void
	end_rendering();

	void
	render(
		const_index_buffer_ptr,
		first_vertex,
		vertex_count,
		indexed_primitive_type::type ptype,
		primitive_count,
		first_index
	);

	void
	render(
		first_vertex,
		vertex_count,
		nonindexed_primitive_type::type ptype
	);

	void
	set_vertex_buffer(
		const_vertex_buffer_ptr
	);

	void
	unset_vertex_buffer(
		const_vertex_buffer_ptr
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
		light_index,
		bool enable
	);

	void
	light(
		light_index,
		renderer::light const &
	);

	void
	enable_clip_plane(
		clip_plane_index,
		bool enable
	);

	void
	clip_plane(
		clip_plane_index,
		renderer::clip_plane const &
	);

	void
	scissor_area(
		renderer::scissor_area const &
	);

	void
	sampler_stage_op(
		stage_type,
		renderer::sampler_stage_op::type,
		renderer::sampler_stage_op_value::type
	);

	void
	sampler_stage_arg(
		stage_type,
		renderer::sampler_stage_arg::type,
		renderer::sampler_stage_arg_value::type
	);

	void
	texture(
		texture::const_base_ptr,
		stage_type
	);

	void
	transform(
		matrix_mode::type,
		matrix4 const &
	);

	void
	target(
		renderer::target_ptr
	);

	glsl::program_ptr const
	create_glsl_program();

	glsl::vertex_shader_ptr const
	create_glsl_vertex_shader(
		glsl::string const &
	);

	glsl::pixel_shader_ptr const
	create_glsl_pixel_shader(
		glsl::string const &
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

	vertex_buffer_ptr const
	create_vertex_buffer(
		vf::dynamic::format const &,
		size_type size,
		resource_flags_field const &
	);

	index_buffer_ptr const
	create_index_buffer(
		index::dynamic::format::type,
		size_type size,
		resource_flags_field const &
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

	sge::window::instance_ptr const
	window() const;
private:
	template<
		typename Ptr
	>
	Ptr const
	add_resource(
		Ptr
	);

	void
	reinit_resources();

	void
	release_resources();

	void
	set_index_buffer(
		renderer::const_index_buffer_ptr
	);

	d3d9::d3d_device_ptr const device_;

	renderer::caps const caps_;

	d3d9::resource_list resources_;

	//renderer::const_vertex_buffer_ptr vb;

	//renderer::const_index_buffer_ptr ib;
};

}
}

#endif
