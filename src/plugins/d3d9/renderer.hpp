/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_RENDERER_HPP_INCLUDED
#define SGE_D3D9_RENDERER_HPP_INCLUDED

#include "vertex_format.hpp"
#include "resource.hpp"
#include "d3dinclude.hpp"
#include <sge/math/matrix.hpp>
#include <sge/math/vector.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/renderer/renderer_parameters.hpp>
#include <sge/renderer/renderer_system.hpp>
#include <sge/win32_window.hpp>

namespace sge
{
namespace d3d9
{

class renderer : public sge::renderer {
public:
	renderer(
		d3d_device_ptr device,
		const renderer_parameters& param,
		adapter_type adapter,
		win32_window_ptr wnd,
		d3d_ptr sys);

	const texture_ptr create_texture(
		texture::const_pointer data,
		const texture::dim_type& dim,
		const filter_args& filter,
		resource_flag_t flags);

	const volume_texture_ptr create_volume_texture(
		volume_texture::const_pointer data,
		const volume_texture::box_type& box,
		const filter_args& filter,
		resource_flag_t flags);

	const cube_texture_ptr create_cube_texture(
		const cube_texture::cube_side_array* data,
		cube_texture::size_type size,
		const filter_args& filter,
		resource_flag_t flags);

	const vertex_buffer_ptr create_vertex_buffer(
		const sge::vertex_format& format,
		vertex_buffer::size_type size,
		resource_flag_t flags,
		vertex_buffer::const_pointer data);

	const index_buffer_ptr create_index_buffer(
		index_buffer::size_type size,
		resource_flag_t flags,
		index_buffer::const_pointer data);

	const render_target_ptr  create_render_target(
		const render_target::dim_type&);

	void set_state(const renderer_state_list&);
	void push_state(const renderer_state_list&);
	void pop_level();

	void set_texture(texture_base_ptr tex, stage_type stage);
	void set_material(const material& m);
	void set_texture_stage_op(stage_type stage, texture_stage_op::type type, texture_stage_op_value::type value);
	void set_texture_stage_arg(stage_type stage, texture_stage_arg::type type, texture_stage_arg_value::type value);
	void set_viewport(const viewport&);
	void enable_light(light_index index, bool enable);
	void set_light(light_index index, const light&);

	const glsl::program_ptr create_glsl_program(
		const std::string& vertex_shader_source,
		const std::string& pixel_shader_source);

	void set_glsl_shader(glsl::program_ptr);

	const render_target_ptr get_render_target() const;

	void begin_rendering();
	void end_rendering();
	void render(vertex_buffer_ptr vb,
	            index_buffer_ptr ib,
	            sge::vertex_buffer::size_type first_vertex,
	            sge::vertex_buffer::size_type num_vertices,
	            indexed_primitive_type::type ptype,
	            sge::index_buffer::size_type pcount,
	            sge::index_buffer::size_type first_index);
	void render(vertex_buffer_ptr vb,
	            sge::vertex_buffer::size_type first_vertex,
	            sge::vertex_buffer::size_type num_vertices,
	            nonindexed_primitive_type::type ptype);

	void reset(const renderer_parameters* param);
	void set_render_target(texture_ptr target);
	void setviewport(const viewport&);

	void transform(const math::space_matrix&);
	void projection(const math::space_matrix&);

	const window_ptr get_window() const;
	const screen_size_t screen_size() const;
	const renderer_caps& caps() const;
private:
	d3d_ptr                     sys;
	d3d_device_ptr              device;
	adapter_type                adapter;
	renderer_parameters         parameters;
	win32_window_ptr            render_window;
	renderer_caps               caps_;
	d3d_surface_ptr             default_render_target;
	resource_list               resources;
	d3d_vertex_declaration_ptr  vertex_declaration;
	vertex_buffer_ptr           vb;
	index_buffer_ptr            ib;
private:
	void init();
	void release_resources();
	void set_vertex_buffer(vertex_buffer_ptr buffer);
	void set_index_buffer(index_buffer_ptr buffer);

	friend class resource;
};

}
}

#endif
