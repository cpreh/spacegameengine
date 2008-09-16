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


#ifndef SGE_OPENGL_DEVICE_HPP_INCLUDED
#define SGE_OPENGL_DEVICE_HPP_INCLUDED

#include <sge/config.h>
#include "target.hpp"
#include "fbo_target.hpp"
#if defined(SGE_WINDOWS_PLATFORM)
#include "wgl_context.hpp"
#include "wgl_current.hpp"
#include <sge/windows/gdi_device.hpp>
#include <sge/windows/window.hpp>
#include <sge/windows/windows.hpp>
#elif defined(SGE_HAVE_X11)
#include <X11/Xlib.h>
#include <GL/glx.h>
#include "glx_visual.hpp"
#include "glx_current.hpp"
#include "glx_context.hpp"
#include <sge/x11/colormap.hpp>
#include <sge/x11/xf86_vidmode_array.hpp>
#include <sge/x11/xf86_resolution.hpp>
#include <sge/x11/window.hpp>
#else
#error "Implement me!"
#endif
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/window.hpp>
#include <sge/scoped_connection.hpp>
#include "common.hpp"
#include <boost/scoped_ptr.hpp>
#include <boost/signals/trackable.hpp>
#include <stack>

namespace sge
{
namespace ogl
{

class device : public renderer::device, public boost::signals::trackable {
public:
	device(
		const renderer::parameters& param,
		renderer::adapter_type adapter,
		window_ptr wnd);

	void begin_rendering();
	void end_rendering();
	void render(
		renderer::const_vertex_buffer_ptr vb,
		renderer::const_index_buffer_ptr ib,
		renderer::vertex_buffer::size_type first_vertex,
		renderer::vertex_buffer::size_type num_vertices,
		renderer::indexed_primitive_type::type ptype,
		renderer::index_buffer::size_type pcount,
		renderer::index_buffer::size_type first_index);
	void render(
		renderer::const_vertex_buffer_ptr vb,
		renderer::vertex_buffer::size_type first_vertex,
		renderer::vertex_buffer::size_type num_vertices,
		renderer::nonindexed_primitive_type::type ptype);

	void set_state(const renderer::state_list &);

	void push_state(const renderer::state_list &);

	void pop_level();

	void set_texture(
		renderer::const_texture_base_ptr tex,
		renderer::stage_type stage);
	void set_material(const renderer::material& mat);

	void transform(const math::space_matrix& matrix);
	void projection(const math::space_matrix& matrix);
	void texture_transform(math::space_matrix const & matrix);

	void set_render_target(renderer::texture_ptr target);
	void set_viewport(const renderer::viewport&);
	const renderer::viewport &get_viewport() const;
	void enable_light(renderer::light_index index, bool enable);
	void set_light(renderer::light_index index, const renderer::light&);
	void set_texture_stage_op(
		renderer::stage_type stage,
		renderer::texture_stage_op::type,
		renderer::texture_stage_op_value::type);
	void set_texture_stage_arg(
		renderer::stage_type stage,
		renderer::texture_stage_arg::type,
		renderer::texture_stage_arg_value::type);

	renderer::glsl::program_ptr const
	create_glsl_program(
		renderer::glsl::string const &vertex_shader_source,
		renderer::glsl::string const &pixel_shader_source);
	renderer::glsl::program_ptr const
	create_glsl_program(
		renderer::glsl::istream &vertex_shader_source,
		renderer::glsl::istream &pixel_shader_source);
	
	void set_glsl_program(
		renderer::glsl::program_ptr);

	renderer::const_target_ptr const get_target() const;

	renderer::texture_ptr const
	create_texture(
		renderer::texture::dim_type const &,
		renderer::color_format::type,
		renderer::filter_args const &,
		renderer::texture::resource_flag_type);

	/*const renderer::volume_texture_ptr
	create_volume_texture(
		renderer::volume_texture::image_view_array const &,
		const renderer::filter_args& filter,
		renderer::volume_texture::resource_flag_type flags);*/

	renderer::cube_texture_ptr const
	create_cube_texture(
		renderer::cube_texture::size_type border_size,
		renderer::color_format::type,
		renderer::filter_args const &,
		renderer::texture::resource_flag_type);

	renderer::vertex_buffer_ptr const
	create_vertex_buffer(
		renderer::vertex_format const &,
		renderer::vertex_buffer::size_type size,
		renderer::vertex_buffer::resource_flag_type flags);

	renderer::index_buffer_ptr const
	create_index_buffer(
		renderer::index_format::type,
		renderer::index_buffer::size_type sz,
		renderer::index_buffer::resource_flag_type flags);

	renderer::caps const &get_caps() const;
	renderer::screen_size_t const screen_size() const;
	window_ptr const get_window() const;

	void set_stencil_func();
	void set_blend_func();
private:
	GLenum get_clear_bit(renderer::bool_state::type) const;
	template<typename T>
		T get_state(const T&) const;
	const renderer::any_state& get_any_state(
		const renderer::any_state& state) const;

	void set_vertex_buffer(renderer::const_vertex_buffer_ptr vb);
	void set_index_buffer(renderer::const_index_buffer_ptr ib);
	const fbo_target_ptr create_render_target(
		const renderer::target::dim_type&);

	renderer::parameters          param;
	renderer::caps                caps_;
	renderer::state_list          current_states;
#if defined(SGE_WINDOWS_PLATFORM)
	windows::window_ptr               wnd;
	boost::scoped_ptr<windows::gdi_device>  hdc;
	boost::scoped_ptr<wgl_context> context;
	boost::scoped_ptr<wgl_current> current;
#elif defined(SGE_HAVE_X11)
	void reset_viewport_on_map(const XEvent&);
	void reset_viewport_on_configure(const XEvent&);
	void center_viewport(int w, int h);

	x11::display_ptr                      dsp;
	scoped_connection                     map_callback;
	boost::scoped_ptr<glx_visual>         visual;
	glx_context_ptr                       context;
	boost::scoped_ptr<x11::colormap>      colormap;
	x11::window_ptr                       wnd;
	boost::scoped_ptr<glx_current>        current;
	boost::scoped_ptr<
		x11::xf86_vidmode_array>      modes;
	x11::xf86_resolution_ptr              resolution;
	scoped_connection_manager             con_manager;
#endif
	target_ptr                            render_target_;
	typedef std::stack<
		renderer::state_list
	> stack_type;
	stack_type                            state_levels;
};

}
}

#endif
