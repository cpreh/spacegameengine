/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "resource_list.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/windows/window_fwd.hpp>

namespace sge
{
namespace d3d9
{

class device : public sge::renderer::device {
public:
	device(
		d3d_device_ptr device,
		renderer::parameters const &param,
		D3DPRESENT_PARAMETERS const &,
		windows::window_ptr,
		renderer::caps const &)

	void begin_rendering();
	void end_rendering();
	void render(
		renderer::const_vertex_buffer_ptr vb,
		renderer::const_index_buffer_ptr ib,
		renderer::size_type first_vertex,
		renderer::size_type num_vertices,
		renderer::indexed_primitive_type::type ptype,
		renderer::size_type primitive_count,
		renderer::size_type first_index);
	void render(
		renderer::const_vertex_buffer_ptr vb,
		renderer::size_type first_vertex,
		renderer::size_type num_vertices,
		renderer::nonindexed_primitive_type::type ptype);

	void state(
		renderer::state::list const &);
	void push_state(
		renderer::state::list const &);
	void pop_state();

	void material(
		renderer::material const &mat);
	void enable_light(
		renderer::light_index index,
		bool enable);
	void light(
		renderer::light_index index,
		renderer::light const &);
	void texture_stage_op(
		renderer::stage_type stage,
		renderer::texture_stage_op::type,
		renderer::texture_stage_op_value::type);
	void texture_stage_arg(
		renderer::stage_type stage,
		renderer::texture_stage_arg::type,
		renderer::texture_stage_arg_value::type);

	void texture(
		renderer::const_texture_base_ptr tex,
		renderer::stage_type stage);

	void transform(
		renderer::any_matrix const &mat);
	void projection(
		renderer::any_matrix const &mat);
	void texture_transform(
		renderer::any_matrix const &mat);

	void target(
		renderer::texture_ptr);

	void viewport(
		renderer::viewport const &);

	void viewport_mode(
		renderer::viewport_mode::type);

	renderer::glsl::program_ptr const
	create_glsl_program(
		renderer::glsl::optional_string const &vertex_shader_source,
		renderer::glsl::optional_string const &pixel_shader_source);

	renderer::glsl::program_ptr const
	create_glsl_program(
		renderer::glsl::optional_istream const &vertex_shader_source,
		renderer::glsl::optional_istream const &pixel_shader_source);

	void glsl_program(
		renderer::glsl::program_ptr);

	renderer::const_target_ptr const
	target() const;

	renderer::texture_ptr const
	create_texture(
		renderer::dim_type const &dim,
		image::color::format::type format,
		renderer::filter::texture const &filter,
		renderer::resource_flag_t flags);

	/*const volume_texture_ptr create_volume_texture(
		volume_texture::image_view_array const &,
		filter::texture const &filter,
		resource_flag_t flags);*/

	renderer::cube_texture_ptr const
	create_cube_texture(
		renderer::size_type border_size,
		image::color::format::type format,
		renderer::filter::texture const &filter,
		renderer::resource_flag_t flags);

	renderer::vertex_buffer_ptr const
	create_vertex_buffer(
		renderer::vf::dynamic_format const &,
		renderer::size_type size,
		renderer::resource_flag_t flags);

	renderer::index_buffer_ptr const
	create_index_buffer(
		renderer::index::format::type,
		renderer::size_type size,
		renderer::resource_flag_t flags);

	renderer::caps const
	caps() const;

	renderer::screen_size const
	screen_size() const;

	sge::window::instance_ptr const
	window() const;
private:
	template<
		typename Ptr
	>
	Ptr const
	add_resource(
		Ptr);

	void init();
	void release_resources();
	void set_vertex_buffer(
		renderer::const_vertex_buffer_ptr buffer);
	void set_index_buffer(
		renderer::const_index_buffer_ptr buffer);

	d3d_device_ptr const device_;
	windows::window_ptr const wnd;
	renderer::caps const caps_;
	d3d_surface_ptr default_render_target;
	resource_list resources;
	d3d_vertex_declaration_ptr vertex_declaration;
	renderer::const_vertex_buffer_ptr vb;
	renderer::const_index_buffer_ptr ib;
};

}
}

#endif
