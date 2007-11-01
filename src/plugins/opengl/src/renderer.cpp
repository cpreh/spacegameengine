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


#include <iostream>
#include "../../../types.hpp"
#include "../../../ptr_cast.hpp"
#include "../../../bit.hpp"
#include "../../../renderer/types.hpp"
#include "../../../renderer/renderer_system.hpp"
#include "../../../renderer/primitive.hpp"
#include "../../../exception.hpp"
#include "../renderer.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../vertex_buffer.hpp"
#include "../texture.hpp"
#include "../cube_texture.hpp"
#include "../volume_texture.hpp"
#include "../conversion.hpp"
#include "../default_render_target.hpp"
#include "../light.hpp"
#include "../enable.hpp"
#include "../multi_texture.hpp"
#include "../texture_stage.hpp"
#include "../basic_buffer_impl.hpp"
#include "../get.hpp"
#include "../shader.hpp"
#include "../program.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../../../windows.hpp"
#include "../../../win32_window.hpp"
#elif SGE_LINUX_PLATFORM
#include "../../../x_window.hpp"
#endif
#include "../common.hpp"

// TODO: consistent error checking

// TODO: move the Xerror code somewhere more appropriate

#ifdef SGE_LINUX_PLATFORM

int handler(Display* const d, XErrorEvent* const e)
{
	boost::array<char,1024> buf;
	XGetErrorText(d,e->error_code,buf.c_array(),buf.size());
	std::cerr << "X Error: " << buf.data() << '\n';
	return 0;
}
#endif

// TODO: maybe support different adapters?
sge::ogl::renderer::renderer(const renderer_parameters& param, const unsigned adapter, const window_ptr wnd_param)
 : param(param),
   clearflags(0)
#ifdef SGE_LINUX_PLATFORM
   , dsp(new x_display())
#endif
   , current_viewport(0,0,0,0)
{
	if(adapter > 0)
		std::cerr << "stub: adapter cannot be > 0 for opengl plugin (adapter was " << adapter << ")\n";

	bool windowed = param.windowed;
#ifdef SGE_WINDOWS_PLATFORM
	const unsigned color_depth = bit_depth_bit_count(param.mode.depth);
	if(!windowed)
	{
		DEVMODE settings;
		memset(&settings,0,sizeof(DEVMODE));
		settings.dmSize = sizeof(DEVMODE);
		settings.dmPelsWidth    = param.mode.width();
		settings.dmPelsHeight   = param.mode.height();
		settings.dmBitsPerPel   = color_depth;
		settings.dmDisplayFrequency = param.mode.refresh_rate;
		settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH|DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
		if(ChangeDisplaySettings(&settings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			std::cerr << "Cannot change resolution to " << param.mode << "! Reverting to window mode!\n";
			windowed = false;
		}
	}

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size Of This Pixel Format Descriptor
			1,                      // Version Number
			PFD_DRAW_TO_WINDOW |    // Format Must Support Window
			PFD_SUPPORT_OPENGL |    // Format Must Support OpenGL
			PFD_DOUBLEBUFFER,       // Must Support Double Buffering
			PFD_TYPE_RGBA,          // Request An RGBA Format
			BYTE(color_depth),      // Select Our Color Depth
			0, 0, 0, 0, 0, 0,       // Color Bits Ignored
			0,                      // No Alpha Buffer
			0,                      // Shift Bit Ignored
			0,                      // No Accumulation Buffer
			0, 0, 0, 0,             // Accumulation Bits Ignored
			16,                     // 16Bit Z-Buffer (Depth Buffer)
			0,                      // Stencil Buffer
			0,                      // No Auxiliary Buffer
			PFD_MAIN_PLANE,         // Main Drawing Layer
			0,                      // Reserved
			0, 0, 0                 // Layer Masks Ignored
	};

	if(!wnd_param)
		wnd.reset(new win32_window(window::window_size(param.mode.width(),param.mode.height())));
	else
		wnd = polymorphic_pointer_cast<win32_window>(wnd_param);

	hdc.reset(new gdi_device(wnd->hwnd(), gdi_device::get_tag()));

	const int pixel_format = ChoosePixelFormat(hdc->hdc(), &pfd);
	if(pixel_format == 0)
		throw exception("ChoosePixelFormat() failed");
	if(SetPixelFormat(hdc->hdc(), pixel_format, &pfd) == FALSE)
		throw exception("SetPixelFormat() failed");

	context.reset(new wgl_context(*hdc));

	current.reset(new wgl_current(*hdc, *context));

#elif SGE_LINUX_PLATFORM
	XSetErrorHandler(handler);
	const int screen = DefaultScreen(dsp->get());

	if(!windowed)
	{
		modes.reset(new xf86_vidmode_array(dsp, screen));
		resolution = modes->switch_to_mode(param.mode);
		if(!resolution)
		{
			std::cerr << "Warning: No resolution matches against " << param.mode << "! Falling back to window mode!\n";
			windowed = true;
		}
	}

	const int attributes[] = {GLX_RGBA, GLX_DOUBLEBUFFER, GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_DEPTH_SIZE, 24, None};
	visual.reset(new glx_visual(dsp, screen, attributes));

	context.reset(new glx_context(dsp, visual->visual_info()));

	colormap.reset(new x_colormap(dsp, visual->visual_info()));

	XSetWindowAttributes swa;
	swa.colormap = colormap->colormap();
	swa.border_pixel = 0;
	swa.background_pixel = 0;
	swa.override_redirect = windowed ? False : True;
	swa.event_mask = StructureNotifyMask;

	if(wnd_param)
		wnd = polymorphic_pointer_cast<x_window>(wnd_param);
	else
		wnd.reset(new x_window(window::window_pos(0,0), window::window_size(param.mode.width(), param.mode.height()), string(), dsp, swa, visual->visual_info()));

	if(!windowed)
		XMapWindow(dsp->get(), wnd->get_window());
	else
		XMapRaised(dsp->get(), wnd->get_window());

	current.reset(new glx_current(dsp, *wnd, context));

	XSync(dsp->get(),False);
#endif
	if(glewInit() != GLEW_OK)
		throw exception("glewInit() failed");

	set_blend_func(source_blend_func::src_alpha, dest_blend_func::inv_src_alpha);

	// TODO: implement caps
	_caps.adapter_number = adapter;
	_caps.max_tex_size = get_int(GL_MAX_TEXTURE_SIZE);
	_caps.max_anisotropy_level = get_int(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);

	set_render_target();
}

void sge::ogl::renderer::begin_rendering()
{
	glClear(clearflags);
}

sge::index_buffer_ptr sge::ogl::renderer::create_index_buffer(const index_buffer::size_type size,
                                                              const resource_flag_t flags,
                                                              const index_buffer::const_pointer data)
{
	return index_buffer_ptr(new index_buffer(size,flags,data));
}

sge::ogl::fbo_render_target_ptr sge::ogl::renderer::create_render_target(const render_target::size_type width,
                                                                         const render_target::size_type height)
{
	return fbo_render_target_ptr(new fbo_render_target(width,height));
}

sge::texture_ptr sge::ogl::renderer::create_texture(const texture::const_pointer src,
                                                    const texture::size_type width,
                                                    const texture::size_type height,
                                                    const filter_args& filter,
                                                    const resource_flag_t flags)
{
	return texture_ptr(new texture(src, width, height, filter, flags));
}

sge::vertex_buffer_ptr sge::ogl::renderer::create_vertex_buffer(const sge::vertex_format& format,
                                                                const vertex_buffer::size_type size,
                                                                const resource_flag_t flags,
                                                                const vertex_buffer::const_pointer src)
{
	return vertex_buffer_ptr(new vertex_buffer(size,format,flags,src));
}

sge::volume_texture_ptr sge::ogl::renderer::create_volume_texture(const volume_texture::const_pointer src,
                                                                  const volume_texture::size_type width,
                                                                  const volume_texture::size_type height,
                                                                  const volume_texture::size_type depth,
                                                                  const filter_args& filter,
                                                                  const resource_flag_t flags)
{
	return volume_texture_ptr(new volume_texture(src, width, height, depth, filter, flags));
}

sge::cube_texture_ptr sge::ogl::renderer::create_cube_texture(const cube_side_array* const src,
                                                              const cube_texture::size_type sz,
                                                              const filter_args& filter,
                                                              const resource_flag_t flags)
{
	return cube_texture_ptr(new cube_texture(src, sz, filter, flags));
}

void sge::ogl::renderer::end_rendering()
{
#ifdef SGE_LINUX_PLATFORM
	glXSwapBuffers(dsp->get(), wnd->get_window());
	if(is_error())
		throw exception("glXSwapBuffers() failed!");
#elif SGE_WINDOWS_PLATFORM
	if(wglSwapLayerBuffers(hdc->hdc(), WGL_SWAP_MAIN_PLANE) == FALSE)
		throw exception("wglSwapLayerBuffers() failed!");
#endif
}

const sge::renderer_caps& sge::ogl::renderer::caps() const
{
	return _caps;
}

sge::window_ptr sge::ogl::renderer::get_window() const
{
	return wnd;
}

sge::screen_size_t sge::ogl::renderer::screen_size() const
{
	return param.mode.size;
}

void sge::ogl::renderer::render(const vertex_buffer_ptr vb,
                                const index_buffer_ptr ib,
                                const sge::vertex_buffer::size_type first_vertex,
                                const sge::vertex_buffer::size_type num_vertices,
                                const indexed_primitive_type::type ptype,
                                const sge::index_buffer::size_type pcount,
                                const sge::index_buffer::size_type first_index)
{
	if(!vb)
		throw exception("vb may not be 0 for renderer::render!");
	if(!ib)
		throw exception("ib may not be 0 for renderer::render for indexed primitives!");

	set_vertex_buffer(vb);
	set_index_buffer(ib);

	const GLenum prim_type = convert_cast<GLenum>(ptype);

	glDrawElements(prim_type,
	               indices_per_primitive(ptype) * pcount,
	               GL_UNSIGNED_INT,
	               vbo_offset(first_index * sizeof(sge::index_buffer::value_type)));

	if(is_error())
		throw exception("opengl error during rendering an indexed array!");
}

void sge::ogl::renderer::render(const vertex_buffer_ptr vb,
                                const vertex_buffer::size_type first_vertex,
                                const vertex_buffer::size_type num_vertices,
                                const nonindexed_primitive_type::type ptype)
{
	if(!vb)
		throw exception("vb may not be 0 for renderer::render!");

	set_vertex_buffer(vb);
	set_index_buffer(index_buffer_ptr());

	const GLenum prim_type = convert_cast<GLenum>(ptype);

	glDrawArrays(prim_type,
	             static_cast<GLsizei>(first_vertex),
	             static_cast<GLint>(num_vertices));
	if(is_error())
		throw exception("opengl error during rendering an non indexed array!");

}

void sge::ogl::renderer::set_bool_state(const bool_state::type state, const bool_type value)
{
	switch(state) {
	case bool_state::clear_backbuffer:
		set_bit(GL_COLOR_BUFFER_BIT, clearflags, value);
		break;
	case bool_state::clear_zbuffer:
		set_bit(GL_DEPTH_BUFFER_BIT, clearflags, value);
		break;
	case bool_state::clear_stencil:
		set_bit(GL_STENCIL_BUFFER_BIT, clearflags, value);
		break;
	default:
		const GLenum glstate = convert_cast<GLenum>(state);
		enable(glstate, value);
	}
	if(is_error())
		throw exception("set_bool_state() failed!");
}

void sge::ogl::renderer::set_float_state(const float_state::type state, const float_type value)
{
	switch(state) {
	case float_state::zbuffer_clear_val:
		glClearDepth(value);
		break;
	case float_state::fog_start:
	case float_state::fog_end:
	case float_state::fog_density:
		glFogf(convert_fog_float_state(state), value);
		break;
	}
	if(is_error())
		throw exception("set_float_state() failed!");
}

void sge::ogl::renderer::set_color_state(const color_state::type state, const color value)
{
	switch(state) {
	case color_state::clear_color:
		glClearColor(red_part_rgba_f(value),green_part_rgba_f(value),blue_part_rgba_f(value),alpha_part_rgba_f(value));
		break;
	case color_state::ambient_light_color:
		{
			const color4 fc = color_to_color4(value);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, reinterpret_cast<const GLfloat*>(&fc));
		}
		break;
	case color_state::fog_color:
		{
			const color4 fc = color_to_color4(value);
			glFogfv(GL_FOG_COLOR, reinterpret_cast<const GLfloat*>(&fc));
		}
		break;
	}
	if(is_error())
		throw exception("set_color_state() failed!");
}

void sge::ogl::renderer::set_int_state(const int_state::type state, const int_type value)
{
	switch(state) {
	case int_state::stencil_clear_val:
		glClearStencil(value);
		break;
	default:
		throw exception("Invalid int_state!");
	}
	if(is_error())
		throw exception("set_int_state() failed!");

}

void sge::ogl::renderer::set_fog_mode(const fog_mode::type mode)
{
	glFogi(GL_FOG_MODE, convert_cast<GLenum>(mode));
	if(is_error())
		throw exception("set_fog_mode() failed!");
}

void sge::ogl::renderer::set_cull_mode(const cull_mode::type mode)
{
	const GLenum glmode = convert_cast<GLenum>(mode);
	glCullFace(glmode);

	if(is_error())
		throw exception("glCullMode() failed!");
}

void sge::ogl::renderer::set_depth_func(const depth_func::type func)
{
	const GLenum glfunc = convert_cast<GLenum>(func);
	glDepthFunc(glfunc);

	if(is_error())
		throw exception("glDepthFunc() failed!");
}

void sge::ogl::renderer::set_stencil_func(const stencil_func::type func, const signed_type value, const unsigned_type mask)
{
	const GLenum glfunc = convert_cast<GLenum>(func);
	glStencilFunc(glfunc, value, mask);

	if(is_error())
		throw exception("glStencilFunc() failed!");
}

void sge::ogl::renderer::set_blend_func(const source_blend_func::type source, const dest_blend_func::type dest)
{
	const GLenum glsource = convert_cast<GLenum>(source),
	             gldest   = convert_cast<GLenum>(dest);

	glBlendFunc(glsource, gldest);

	if(is_error())
		throw exception("glBlendFunc() failed!");
}

void sge::ogl::renderer::set_draw_mode(const draw_mode::type mode)
{
	const GLenum glmode = convert_cast<GLenum>(mode);

	glPolygonMode(GL_FRONT_AND_BACK, glmode);

	if(is_error())
		throw exception("glPolygonMode() failed!");
}

void sge::ogl::renderer::set_material(const material& mat)
{
	const GLenum face = GL_FRONT_AND_BACK;
	glMaterialfv(face, GL_AMBIENT, reinterpret_cast<const GLfloat*>(&mat.ambient));
	glMaterialfv(face, GL_DIFFUSE, reinterpret_cast<const GLfloat*>(&mat.diffuse));
	glMaterialfv(face, GL_SPECULAR, reinterpret_cast<const GLfloat*>(&mat.specular));
	glMaterialfv(face, GL_EMISSION, reinterpret_cast<const GLfloat*>(&mat.emissive));
	glMaterialf(face, GL_SHININESS, mat.power);
}

void sge::ogl::renderer::set_viewport(const viewport& v)
{
	current_viewport = v;
	glViewport(v.x, v.y, v.w, v.h);
}

void sge::ogl::renderer::reset_viewport()
{
	set_viewport(current_viewport);
}

const sge::viewport &sge::ogl::renderer::get_viewport() const
{
	return current_viewport;
}

void sge::ogl::renderer::transform(const math::space_matrix& matrix)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(math::transpose(matrix).data());
}

void sge::ogl::renderer::projection(const math::space_matrix& matrix)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(math::transpose(matrix).data());
}

void sge::ogl::renderer::set_render_target(const texture_ptr target)
{
	if(!target)
	{
		_render_target.reset(new default_render_target(wnd));
		_render_target->bind_me();
		set_viewport(viewport(0,0,wnd->width(),wnd->height()));
		return;
	}

	const shared_ptr<texture> p(dynamic_pointer_cast<texture>(target));
	const fbo_render_target_ptr ntarget = create_render_target(p->width(),p->height());
	_render_target = ntarget;
	ntarget->bind_texture(p);
	set_viewport(viewport(0,0,static_cast<screen_unit>(p->width()),static_cast<screen_unit>(p->height())));
}

sge::render_target_ptr sge::ogl::renderer::get_render_target() const
{
	return _render_target;
}

void sge::ogl::renderer::set_texture(const texture_base_ptr tex, const stage_type stage)
{
	set_texture_level(stage);

	glDisable(GL_TEXTURE_1D);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_3D);
	if(!tex)
		return;
	texture_base* const b = ptr_cast<texture_base*>(tex.get());
	glEnable(b->type());
	b->bind_me();
}

void sge::ogl::renderer::enable_light(const light_index index, const bool enable_)
{
	const GLenum glindex = convert_light_index(index);
	enable(glindex, enable_);
}

void sge::ogl::renderer::set_light(const light_index index, const light& l)
{
	const GLenum glindex = convert_light_index(index);

	set_light_color4(glindex, GL_AMBIENT, l.ambient);
	set_light_color4(glindex, GL_DIFFUSE, l.diffuse);
	set_light_color4(glindex, GL_SPECULAR, l.specular);

	const math::vector4 pos(l.pos, 1);
	set_light_pos(glindex, pos);

	set_light_dir(glindex, l.dir);
	
	set_light_float(glindex, GL_CONSTANT_ATTENUATION, l.const_attenuation);
	set_light_float(glindex, GL_LINEAR_ATTENUATION, l.linear_attenuation);
	set_light_float(glindex, GL_QUADRATIC_ATTENUATION, l.quadratic_attenuation);

	set_light_float(glindex, GL_SPOT_EXPONENT, l.distribution_exponent);
	set_light_float(glindex, GL_SPOT_CUTOFF, l.cutoff_angle);
}

void sge::ogl::renderer::set_texture_stage_op(const stage_type stage, const texture_stage_op::type op, const texture_stage_op_value::type value)
{
	set_texture_stage(stage, op, value);
	set_texture_stage_scale(value);
}

void sge::ogl::renderer::set_texture_stage_arg(const stage_type stage, const texture_stage_arg::type arg, const texture_stage_arg_value::type value)
{
	set_texture_stage(stage, arg, value);
}

void sge::ogl::renderer::push()
{
	if(get_int(GL_ATTRIB_STACK_DEPTH) > 16)
		std::cerr << "Warning: glPush() stack level is greater than 16 which is the greater than the minimal supported level!\n";

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if(is_error())
		throw exception("glPushAttrib() failed!");
}

void sge::ogl::renderer::pop()
{
	glPopAttrib();

	if(is_error())
		throw exception("glPopAttrib() failed!");
}

sge::glsl::program_ptr sge::ogl::renderer::create_glsl_program(const std::string& vs_source, const std::string& ps_source)
{
	const shader_ptr vs(vs_source == no_shader ? 0 : new shader(GL_VERTEX_SHADER, vs_source)),
	                 ps(ps_source == no_shader ? 0 : new shader(GL_FRAGMENT_SHADER, ps_source));
	const program_ptr prog(new program());
	if(vs)
		prog->attach_shader(vs);
	if(ps)
		prog->attach_shader(ps);
	prog->link();

	return prog;
}

void sge::ogl::renderer::set_glsl_shader(const glsl::program_ptr prog)
{
	if(!prog)
	{
		program::use_ffp();
		return;
	}
	const program_ptr gl_prog(dynamic_pointer_cast<program>(prog));
	gl_prog->use();
}

void sge::ogl::renderer::set_vertex_buffer(const sge::vertex_buffer_ptr vb)
{
	if(!vb)
	{
		vertex_buffer::unbind();
		return;
	}
	vertex_buffer* const ovb = ptr_cast<vertex_buffer*>(vb.get());
	ovb->set_format();
}

void sge::ogl::renderer::set_index_buffer(const sge::index_buffer_ptr ib)
{
	if(!ib)
	{
		index_buffer::unbind();
		return;
	}
	index_buffer* const oib = ptr_cast<index_buffer*>(ib.get());
	oib->bind_me();
}
