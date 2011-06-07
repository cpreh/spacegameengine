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

#include "d3dinclude.hpp"
#include "offscreen_target_fwd.hpp"
#include "onscreen_target_fwd.hpp"
#include "resource_list.hpp"
#include "target_base_fwd.hpp"
#include "state/clear.hpp"
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/window/instance_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/shared_ptr.hpp>

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
		IDirect3D9 *,
		renderer::adapter,
		renderer::parameters const &,
		sge::window::instance &
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
		renderer::indexed_primitive_type::type ptype,
		renderer::primitive_count,
		renderer::first_index
	);

	void
	render_nonindexed(
		renderer::first_vertex,
		renderer::vertex_count,
		renderer::nonindexed_primitive_type::type ptype
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
		renderer::vertex_declaration const *
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
	sampler_stage_op(
		renderer::stage_type,
		renderer::sampler_stage_op::type,
		renderer::sampler_stage_op_value::type
	);

	void
	sampler_stage_arg(
		renderer::stage_type,
		renderer::sampler_stage_arg::type,
		renderer::sampler_stage_arg_value::type
	);

	void
	texture(
		renderer::texture::base const *,
		renderer::stage_type
	);

	void
	transform(
		renderer::matrix_mode::type,
		renderer::matrix4 const &
	);

	void
	target(
		renderer::target *
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
		renderer::glsl::program const *
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
		renderer::vertex_declaration const &,
		renderer::vf::dynamic::part_index,
		renderer::size_type size,
		renderer::resource_flags_field const &
	);

	renderer::index_buffer_ptr const
	create_index_buffer(
		renderer::index::dynamic::format::type,
		renderer::size_type size,
		renderer::resource_flags_field const &
	);

	renderer::onscreen_target &
	onscreen_target() const;

	renderer::target *
	target() const;

	renderer::matrix4 const
	transform(
		renderer::matrix_mode::type
	);

	renderer::caps const
	caps() const;

	sge::window::instance &
	window() const;
private:
	template<
		typename Ptr
	>
	fcppt::shared_ptr<
		Ptr
	> const
	add_resource(
		fcppt::shared_ptr<
			Ptr
		>
	);

	void
	reset();

	void
	reinit_resources();

	void
	release_resources();

	void
	set_index_buffer(
		renderer::index_buffer const &
	);

	D3DPRESENT_PARAMETERS present_parameters_;

	typedef fcppt::scoped_ptr<
		IDirect3DDevice9,
		fcppt::com_deleter
	> d3d_device_scoped_ptr;

	d3d_device_scoped_ptr const device_;

	sge::window::instance &window_;

	renderer::caps const caps_;

	d3d9::resource_list resources_;

	typedef fcppt::scoped_ptr<
		d3d9::onscreen_target
	> onscreen_target_scoped_ptr;

	onscreen_target_scoped_ptr const onscreen_target_;
	
	d3d9::offscreen_target *offscreen_target_;

	d3d9::target_base *target_;

	d3d9::state::clear clear_state_;
};

}
}

#endif
