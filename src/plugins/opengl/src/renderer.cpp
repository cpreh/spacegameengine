/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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


#include "../../../config.h"
#include <boost/foreach.hpp>
#include <boost/variant/apply_visitor.hpp>
#include "../../../bit.hpp"
#include "../../../exception.hpp"
#include "../../../iostream.hpp"
#include "../../../ostream.hpp"
#include "../../../renderer/material.hpp"
#include "../../../renderer/primitive.hpp"
#include "../../../renderer/renderer_system.hpp"
#include "../../../renderer/types.hpp"
#include "../../../renderer/viewport.hpp"
#include "../../../renderer/default_renderer_states.hpp"
#include "../../../math/matrix_impl.hpp"
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
#include "../error.hpp"
#include "../state_visitor.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../../../windows.hpp"
#include "../../../win32_window.hpp"
#elif SGE_LINUX_PLATFORM
#include <boost/bind.hpp>
#include "../../../x_window.hpp"
#endif
#include "../common.hpp"

// TODO: maybe support different adapters?
sge::ogl::renderer::renderer(const renderer_parameters& param,
                             const unsigned adapter,
                             const window_ptr wnd_param)
 : param(param),
   caps_(
   	adapter,
   	"TODO",
	"TODO",
	2048, //get_int(GL_MAX_TEXTURE_SIZE), //FIXME
	get_int(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT)),
   state_levels(*this),
   current_states(default_renderer_states())
#ifdef SGE_LINUX_PLATFORM
   , dsp(new x_display())
#endif
{
	if(adapter > 0)
		sge::cerr << SGE_TEXT("stub: adapter cannot be > 0 for opengl plugin (adapter was ") << adapter << SGE_TEXT(").\n");

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
			sge::cerr << SGE_TEXT("Cannot change resolution to ") << param.mode << SGE_TEXT("! Reverting to window mode!\n");
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
		throw exception(SGE_TEXT("ChoosePixelFormat() failed"));
	if(SetPixelFormat(hdc->hdc(), pixel_format, &pfd) == FALSE)
		throw exception(SGE_TEXT("SetPixelFormat() failed"));

	context.reset(new wgl_context(*hdc));

	current.reset(new wgl_current(*hdc, *context));

#elif SGE_LINUX_PLATFORM
	const int screen = DefaultScreen(dsp->get());

	if(!windowed)
	{
		modes.reset(new xf86_vidmode_array(dsp, screen));
		resolution = modes->switch_to_mode(param.mode);
		if(!resolution)
		{
			sge::cerr << SGE_TEXT("Warning: No resolution matches against ") << param.mode << SGE_TEXT("! Falling back to window mode!\n");
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

 	con_manager.scoped_connect(wnd->register_callback(MapNotify, boost::bind(&renderer::reset_viewport_on_map, this, _1)));
	con_manager.scoped_connect(wnd->register_callback(ResizeRequest, boost::bind(&renderer::reset_viewport_on_resize, this, _1)));

	XSync(dsp->get(), False);
#endif
	if(glewInit() != GLEW_OK)
		throw exception(SGE_TEXT("glewInit() failed!"));

	initialize_vbo();
	initialize_pbo();

	set_render_target();
	set_state(default_renderer_states());
}

void sge::ogl::renderer::begin_rendering()
{
	SGE_OPENGL_SENTRY

	glClear(
		get_clear_bit(bool_state::clear_backbuffer)
		| get_clear_bit(bool_state::clear_zbuffer)
		| get_clear_bit(bool_state::clear_stencil));
}

const sge::index_buffer_ptr sge::ogl::renderer::create_index_buffer(
	const index_buffer::size_type size,
	const resource_flag_t flags,
	const index_buffer::const_pointer data)
{
	return index_buffer_ptr(new index_buffer(size, flags, data));
}

const sge::ogl::fbo_render_target_ptr sge::ogl::renderer::create_render_target(
	const render_target::dim_type& dim)
{
	return fbo_render_target_ptr(new fbo_render_target(dim));
}

const sge::texture_ptr sge::ogl::renderer::create_texture(
	const texture::const_pointer src,
	const texture::dim_type& dim,
	const filter_args& filter,
	const resource_flag_t flags)
{
	return texture_ptr(new texture(src, dim, filter, flags));
}

const sge::vertex_buffer_ptr sge::ogl::renderer::create_vertex_buffer(
	const sge::vertex_format& format,
	const vertex_buffer::size_type size,
	const resource_flag_t flags,
	const vertex_buffer::const_pointer src)
{
	return vertex_buffer_ptr(new vertex_buffer(size,format,flags,src));
}

const sge::volume_texture_ptr sge::ogl::renderer::create_volume_texture(
	const volume_texture::const_pointer src,
 	const volume_texture::box_type& box,
	const filter_args& filter,
	const resource_flag_t flags)
{
#ifndef SGE_OPENGL_HAVE_VOLUME_TEXTURE
	on_not_supported(SGE_TEXT("volume_texture"),
	                 SGE_TEXT("1.2"),
	                 SGE_TEXT("gl_ext_texture3d"));
#else
	return volume_texture_ptr(new volume_texture(src, box, filter, flags));
#endif
}

const sge::cube_texture_ptr sge::ogl::renderer::create_cube_texture(
	const cube_texture::cube_side_array* const src,
	const cube_texture::size_type sz,
	const filter_args& filter,
	const resource_flag_t flags)
{
#ifndef SGE_OPENGL_HAVE_CUBE_TEXTURE
	on_not_supported(SGE_TEXT("cube texture"),
	                 SGE_TEXT("1.3"),
	                 SGE_TEXT("gl_arb_cube_texture"));
#else
	return cube_texture_ptr(new cube_texture(src, sz, filter, flags));
#endif
}

void sge::ogl::renderer::end_rendering()
{
#ifdef SGE_LINUX_PLATFORM
	SGE_OPENGL_SENTRY
	glXSwapBuffers(dsp->get(), wnd->get_window());
#elif SGE_WINDOWS_PLATFORM
	if(wglSwapLayerBuffers(hdc->hdc(), WGL_SWAP_MAIN_PLANE) == FALSE)
		throw exception(SGE_TEXT("wglSwapLayerBuffers() failed!"));
#endif
}

const sge::renderer_caps& sge::ogl::renderer::caps() const
{
	return caps_;
}

const sge::window_ptr sge::ogl::renderer::get_window() const
{
	return wnd;
}

const sge::screen_size_t sge::ogl::renderer::screen_size() const
{
	return param.mode.size;
}

void sge::ogl::renderer::render(
	const vertex_buffer_ptr vb,
	const index_buffer_ptr ib,
	const sge::vertex_buffer::size_type first_vertex,
	const sge::vertex_buffer::size_type num_vertices,
	const indexed_primitive_type::type ptype,
	const sge::index_buffer::size_type pcount,
	const sge::index_buffer::size_type first_index)
{
	if(!vb)
		throw exception(SGE_TEXT("vb may not be 0 for renderer::render!"));
	if(!ib)
		throw exception(SGE_TEXT("ib may not be 0 for renderer::render for indexed primitives!"));

	SGE_OPENGL_SENTRY

	set_vertex_buffer(vb);
	set_index_buffer(ib);

	const GLenum prim_type = convert_cast(ptype);

	const index_buffer& gl_ib = dynamic_cast<const index_buffer&>(*ib);

	glDrawElements(
		prim_type,
		static_cast<GLsizei>(indices_per_primitive(ptype) * pcount),
		GL_UNSIGNED_INT,
		gl_ib.buffer_offset(
			first_index * sizeof(sge::index_buffer::value_type)));
}

void sge::ogl::renderer::render(
	const vertex_buffer_ptr vb,
	const vertex_buffer::size_type first_vertex,
	const vertex_buffer::size_type num_vertices,
	const nonindexed_primitive_type::type ptype)
{
	if(!vb)
		throw exception(SGE_TEXT("vb may not be 0 for renderer::render!"));

	SGE_OPENGL_SENTRY

	set_vertex_buffer(vb);
	set_index_buffer(index_buffer_ptr());

	const GLenum prim_type = convert_cast(ptype);

	glDrawArrays(prim_type,
	             static_cast<GLsizei>(first_vertex),
	             static_cast<GLint>(num_vertices));

}

void sge::ogl::renderer::set_state(const renderer_state_list &states)
{
	const state_visitor visitor(*this);
	BOOST_FOREACH(const any_renderer_state& s, states)
	{
		boost::apply_visitor(visitor, s);
		current_states.insert(s);
	}
}

void sge::ogl::renderer::push_state(const renderer_state_list& states)
{
	renderer_state_list list;
	BOOST_FOREACH(const any_renderer_state& s, states)
		list.insert(get_any_state(s));
	
	state_levels.push(list);
	set_state(states);
}

void sge::ogl::renderer::set_stencil_func()
{
	SGE_OPENGL_SENTRY
	glStencilFunc(
		convert_cast(get_state(stencil_func::off)), // FIXME
		0,
		0); // FIXME
}

void sge::ogl::renderer::set_blend_func()
{
	SGE_OPENGL_SENTRY
	glBlendFunc(
		convert_cast(get_state(source_blend_func::zero)), // FIXME
		convert_cast(get_state(dest_blend_func::zero))); // FIXME
}

GLenum sge::ogl::renderer::get_clear_bit(const bool_state::type s) const
{
	return get_state(s).value() ? convert_clear_bit(s) : 0;
}

template<typename T>
T sge::ogl::renderer::get_state(const T& t) const
{
	const renderer_state_list::const_iterator it = current_states.find(t);
	if(it == current_states.end())
		throw exception(SGE_TEXT("ogl::renderer::get_state(): state not found!"));
	return boost::get<T>(*it);
}

const sge::any_renderer_state& sge::ogl::renderer::get_any_state(const any_renderer_state& state) const
{
	const renderer_state_list::const_iterator it = current_states.find(state);
	if(it == current_states.end())
		throw exception(SGE_TEXT("ogl::renderer::get_any_state(): state not found!"));
	return *it;
}

void sge::ogl::renderer::set_material(const material& mat)
{
	SGE_OPENGL_SENTRY

	const GLenum face = GL_FRONT_AND_BACK;
	glMaterialfv(face, GL_AMBIENT, reinterpret_cast<const GLfloat*>(&mat.ambient));
	glMaterialfv(face, GL_DIFFUSE, reinterpret_cast<const GLfloat*>(&mat.diffuse));
	glMaterialfv(face, GL_SPECULAR, reinterpret_cast<const GLfloat*>(&mat.specular));
	glMaterialfv(face, GL_EMISSION, reinterpret_cast<const GLfloat*>(&mat.emissive));
	glMaterialf(face, GL_SHININESS, mat.power);
}

void sge::ogl::renderer::set_viewport(const viewport& v)
{
	SGE_OPENGL_SENTRY
	glViewport(v.x, v.y, v.w, v.h);
}

#ifdef SGE_LINUX_PLATFORM
void sge::ogl::renderer::reset_viewport_on_map(const XEvent&)
{
	center_viewport();
}

void sge::ogl::renderer::reset_viewport_on_resize(const XEvent&)
{
	center_viewport();
}

void sge::ogl::renderer::center_viewport()
{
	const window::window_size window_dim(wnd->size());
	const pixel_unit x =
		window_dim.w() > screen_width()
		? (window_dim.w() - screen_width()) / 2
		: 0,
	                 y =
		window_dim.h() > screen_height()
		? (window_dim.h() - screen_height()) / 2
		: 0;

	set_viewport(viewport(x, y, screen_width(), screen_height()));
}
#endif

void sge::ogl::renderer::transform(const math::space_matrix& matrix)
{
	SGE_OPENGL_SENTRY

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(math::transpose(matrix).data());
}

void sge::ogl::renderer::projection(const math::space_matrix& matrix)
{
	SGE_OPENGL_SENTRY

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(math::transpose(matrix).data());
}

void sge::ogl::renderer::set_render_target(const texture_ptr target)
{
	if(!target)
	{
		render_target_.reset(new ogl::default_render_target(wnd));
		render_target_->bind_me();
		const window::window_pos offset = wnd->viewport_offset();
		set_viewport(viewport(offset.x(), offset.y(), wnd->width(), wnd->height()));
		return;
	}

	const shared_ptr<texture> p(dynamic_pointer_cast<texture>(target));
	const fbo_render_target_ptr ntarget = create_render_target(p->dim());
	render_target_ = ntarget;
	ntarget->bind_texture(p);
	set_viewport(
		viewport(
			0,
			0,
			static_cast<screen_unit>(p->dim().w()),
			static_cast<screen_unit>(p->dim().h())));
}

const sge::render_target_ptr sge::ogl::renderer::get_render_target() const
{
	return render_target_;
}

void sge::ogl::renderer::set_texture(
	const texture_base_ptr tex,
	const stage_type stage)
{
	set_texture_level(stage);

	disable(GL_TEXTURE_1D);
	disable(GL_TEXTURE_2D);
#ifdef SGE_OPENGL_HAVE_VOLUME_TEXTURE
	disable(detail::volume_texture_type);
#endif
#ifdef SGE_OPENGL_HAVE_CUBE_TEXTURE
	disable(detail::cube_texture_type);
#endif
	if(!tex)
		return;
	texture_base& b = dynamic_cast<texture_base&>(*tex);
	enable(b.type());
	b.bind_me();
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

	const math::vector4 pos(l.pos, static_cast<math::vector4::value_type>(1));
	set_light_pos(glindex, pos);

	set_light_dir(glindex, l.dir);

	set_light_float(glindex, GL_CONSTANT_ATTENUATION, l.const_attenuation);
	set_light_float(glindex, GL_LINEAR_ATTENUATION, l.linear_attenuation);
	set_light_float(glindex, GL_QUADRATIC_ATTENUATION, l.quadratic_attenuation);

	set_light_float(glindex, GL_SPOT_EXPONENT, l.distribution_exponent);
	set_light_float(glindex, GL_SPOT_CUTOFF, l.cutoff_angle);
}

void sge::ogl::renderer::set_texture_stage_op(
	const stage_type stage,
	const texture_stage_op::type op,
	const texture_stage_op_value::type value)
{
	set_texture_stage(stage, op, value);
	set_texture_stage_scale(value);
}

void sge::ogl::renderer::set_texture_stage_arg(
	const stage_type stage,
	const texture_stage_arg::type arg,
	const texture_stage_arg_value::type value)
{
	set_texture_stage(stage, arg, value);
}

void sge::ogl::renderer::pop_level()
{
	state_levels.pop();
}

const sge::glsl::program_ptr sge::ogl::renderer::create_glsl_program(
	const std::string& vs_source,
	const std::string& ps_source)
{
	const shader_ptr vs(new shader(GL_VERTEX_SHADER, vs_source)),
	                 ps(new shader(GL_FRAGMENT_SHADER, ps_source));
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
		// FIXME
		//vertex_buffer::unbind();
		return;
	}
	vertex_buffer& ovb = dynamic_cast<vertex_buffer&>(*vb);
	ovb.set_format();
}

void sge::ogl::renderer::set_index_buffer(const sge::index_buffer_ptr ib)
{
	if(!ib)
	{
		// FIXME
		//index_buffer::unbind();
		return;
	}
	index_buffer& oib = dynamic_cast<index_buffer&>(*ib);
	oib.bind_me();
}
