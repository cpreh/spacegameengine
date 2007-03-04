/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OGL_RENDERER_HPP_INCLUDED
#define SGE_OGL_RENDERER_HPP_INCLUDED

#include "../../types.hpp"
#include "../../renderer/renderer.hpp"
#include "../../window.hpp"
#include "common.hpp"
#include "render_target.hpp"
#include "fbo_render_target.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../../win32.hpp"
#elif SGE_LINUX_PLATFORM
#include <boost/scoped_ptr.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include "../../x_window.hpp"
#include "glx.hpp"
#include "xf86vidmode.hpp"
#endif

namespace sge
{
namespace ogl
{

class renderer : public sge::renderer {
public:
	renderer(const renderer_parameters& param, unsigned adapter);
	~renderer();

	void begin_rendering();
	void end_rendering();
	void render(vertex_buffer_ptr vb, index_buffer_ptr ib, unsigned first_vertex, unsigned num_vertices, primitive_type ptype, unsigned pcount, unsigned first_index = 0);

	void set_int_state(int_state state, int_type value);
	void set_float_state(float_state state, float_type value);
	void set_bool_state(bool_state state, bool_type value);
	void set_texture_stage_op(stage_type stage, stage_op type, stage_op_value value);
	void set_texture_stage_arg(stage_type stage, stage_arg type, stage_arg_value value);
	void set_texture(texture_base_ptr tex, stage_type stage);
	void set_material(const material& mat);
	void transform(const math::space_matrix& matrix);
	void projection(const math::space_matrix& matrix);
	void set_render_target(texture_ptr target = texture_ptr());
	void set_viewport(const viewport&);

	sge::render_target_ptr get_render_target() const;

	texture_ptr create_texture(texture::const_pointer data,
	                           texture::size_type width,
	                           texture::size_type height,
	                           const filter_args& filter,
	                           resource_flag_t flags);

	volume_texture_ptr create_volume_texture(volume_texture::const_pointer data,
	                                         volume_texture::size_type width,
	                                         volume_texture::size_type height,
	                                         volume_texture::size_type depth,
	                                         const filter_args& filter,
	                                         resource_flag_t flags);

	cube_texture_ptr create_cube_texture(const cube_side_array* data,
	                                     cube_texture::size_type size,
	                                     const filter_args& filter,
	                                     resource_flag_t flags);

	vertex_buffer_ptr create_vertex_buffer(const sge::vertex_format& format, vertex_buffer::size_type size, resource_flag_t flags, vertex_buffer::const_pointer data);
	index_buffer_ptr create_index_buffer(index_buffer::size_type size, resource_flag_t flags, index_buffer::const_pointer data);

	const renderer_caps& caps() const;
	screen_size_t screen_size() const;
	window_ptr get_window() const;
private:
	void set_vertex_buffer(sge::vertex_buffer_ptr vb);
	void set_index_buffer(sge::index_buffer_ptr ib);
	fbo_render_target_ptr create_render_target(render_target::size_type width, render_target::size_type height);

	renderer_parameters param;
	bool clear_zbuffer, clear_stencil, clear_back_buffer;
	renderer_caps _caps;
#ifdef SGE_WINDOWS_PLATFORM
	win_hdc    hdc;
	win_hglrc  hglrc;
	window_ptr wnd;
#elif SGE_LINUX_PLATFORM
	x_display dsp;
	x_resource<XVisualInfo*> vi;
	glx_context ct;
	shared_ptr<x_colormap> cm;
	x_window_ptr wnd;
	glx_current_guard cg;
	boost::scoped_ptr<xf86_vidmode_array> modes;
	boost::scoped_ptr<xf86_resolution_guard> resolution_guard;
#endif
	render_target_ptr _render_target;
};

}
}

#endif
