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


#ifndef SGE_OPENGL_RENDERER_HPP_INCLUDED
#define SGE_OPENGL_RENDERER_HPP_INCLUDED

#include <boost/scoped_ptr.hpp>
#include <boost/signals/trackable.hpp>
#include "../../types.hpp"
#include "../../renderer/renderer.hpp"
#include "../../renderer/renderer_parameters.hpp"
#include "../../window.hpp"
#include "../../scoped_connection.hpp"
#include "common.hpp"
#include "render_target.hpp"
#include "fbo_render_target.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../../gdi_device.hpp"
#include "wgl_context.hpp"
#include "wgl_current.hpp"
#include "../../win32_window.hpp"
#include "../../windows.hpp"
#elif SGE_LINUX_PLATFORM
#include "../../x_window.hpp"
#include "xf86vidmode.hpp"
#include "xf86_resolution.hpp"
#include "glx_visual.hpp"
#include "glx_current.hpp"
#include "glx_context.hpp"
#include "x_colormap.hpp"
#include <X11/Xlib.h>
#include <GL/glx.h>
#endif

namespace sge
{
namespace ogl
{

class renderer : public sge::renderer, public boost::signals::trackable {
public:
	renderer(
		const renderer_parameters& param,
		unsigned adapter,
		window_ptr wnd);

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
	            vertex_buffer::size_type first_vertex,
	            vertex_buffer::size_type num_vertices,
	            nonindexed_primitive_type::type ptype);

	void set_state(const any_renderer_state &);
	void set_state(const renderer_state_list &);

	void push_level();
	void push_state(const any_renderer_state &);
	void push_state(const renderer_state_list &);

	void pop_level();

	void set_texture(texture_base_ptr tex, stage_type stage);
	void set_material(const material& mat);

	void transform(const math::space_matrix& matrix);
	void projection(const math::space_matrix& matrix);
	void set_render_target(texture_ptr target = texture_ptr());
	void set_viewport(const viewport&);
	const viewport &get_viewport() const;
	void enable_light(light_index index, bool enable);
	void set_light(light_index index, const light&);
	void set_texture_stage_op(
		stage_type stage,
		texture_stage_op::type,
		texture_stage_op_value::type);
	void set_texture_stage_arg(
		stage_type stage,
		texture_stage_arg::type,
		texture_stage_arg_value::type);

	void push();
	void pop();

	glsl::program_ptr create_glsl_program(
		const std::string& vertex_shader_source = no_shader,
		const std::string& pixel_shader_source = no_shader);
	void set_glsl_shader(glsl::program_ptr);

	sge::render_target_ptr get_render_target() const;

	texture_ptr create_texture(
		texture::const_pointer data,
		const texture::dim_type& dim,
		const filter_args& filter,
		resource_flag_t flags);

	volume_texture_ptr create_volume_texture(
		volume_texture::const_pointer data,
		const volume_texture::box_type& box,
		const filter_args& filter,
		resource_flag_t flags);

	cube_texture_ptr create_cube_texture(
		const cube_side_array* data,
		cube_texture::size_type size,
		const filter_args& filter,
		resource_flag_t flags);

	vertex_buffer_ptr create_vertex_buffer(
		const sge::vertex_format& format,
		vertex_buffer::size_type size,
		resource_flag_t flags,
		vertex_buffer::const_pointer data);

	index_buffer_ptr create_index_buffer(
		index_buffer::size_type size,
		resource_flag_t flags,
		index_buffer::const_pointer data);

	const renderer_caps& caps() const;
	screen_size_t screen_size() const;
	window_ptr get_window() const;

	void set_clear_bit(GLenum bit, bool value);
	void set_stencil_func(GLenum);
	void set_source_blend_func(GLenum);
	void set_dest_blend_func(GLenum);
private:
	void set_blend_func();
	void set_vertex_buffer(sge::vertex_buffer_ptr vb);
	void set_index_buffer(sge::index_buffer_ptr ib);
	fbo_render_target_ptr create_render_target(const render_target::dim_type&);
	void add_push_state(GLbitfield);

	renderer_parameters param;
	GLbitfield          clearflags;
	GLbitfield          accumulated_state;
	GLint               stencil_value;
	GLuint              stencil_mask;
	GLenum              source_blend_func,
	                    dest_blend_func;
#ifdef SGE_WINDOWS_PLATFORM
	win32_window_ptr               wnd;
	boost::scoped_ptr<gdi_device>  hdc;
	boost::scoped_ptr<wgl_context> context;
	boost::scoped_ptr<wgl_current> current;
#elif SGE_LINUX_PLATFORM
	void reset_viewport_on_map(const XEvent&);
	void reset_viewport_on_resize(const XEvent&);

	x_display_ptr                         dsp;
	scoped_connection                     map_callback;
	boost::scoped_ptr<glx_visual>         visual;
	glx_context_ptr                       context;
	boost::scoped_ptr<x_colormap>         colormap;
	x_window_ptr                          wnd;
	boost::scoped_ptr<glx_current>        current;
	boost::scoped_ptr<xf86_vidmode_array> modes;
	xf86_resolution_ptr                   resolution;
	scoped_connection_manager             con_manager;
#endif
	render_target_ptr render_target_;
	renderer_caps     caps_;
};

}
}

#endif
