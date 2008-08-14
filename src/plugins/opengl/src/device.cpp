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


#include <sge/config.h>
#include <boost/foreach.hpp>
#include "../device.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../vertex_buffer.hpp"
#include "../texture.hpp"
#include "../cube_texture.hpp"
#include "../volume_texture.hpp"
#include "../conversion.hpp"
#include "../default_target.hpp"
#include "../light.hpp"
#include "../enable.hpp"
#include "../multi_texture.hpp"
#include "../texture_stage.hpp"
#include "../basic_buffer_impl.hpp"
#include "../get.hpp"
#include "../error.hpp"
#include "../state_visitor.hpp"
#include "../glsl/impl.hpp"
#include "../common.hpp"
#if defined(SGE_WINDOWS_PLATFORM)
#include <sge/windows.hpp>
#include <sge/win32_window.hpp>
#elif defined(SGE_HAVE_X11)
#include <sge/x_window.hpp>
#include <boost/bind.hpp>
#else
#error "Implement me!"
#endif
#include <sge/bit.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <sge/ostream.hpp>
#include <sge/renderer/material.hpp>
#include <sge/renderer/primitive.hpp>
#include <sge/renderer/types.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/default_states.hpp>
#include <sge/math/matrix_impl.hpp>
#include <boost/variant/apply_visitor.hpp>

// TODO: maybe support different adapters?
sge::ogl::device::device(
	const renderer::parameters& param,
	const renderer::adapter_type adapter,
	const window_ptr wnd_param)
 : param(param),
   caps_(
   	adapter,
   	"TODO",
	"TODO",
	2048, //get_int(GL_MAX_TEXTURE_SIZE), //FIXME
	//get_int(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT)),
   0),
   state_levels(*this),
   current_states(renderer::default_states())
#if defined(SGE_HAVE_X11)
   , dsp(new x_display())
#endif
{
	if(adapter > 0)
		sge::cerr << SGE_TEXT("stub: adapter cannot be > 0 for opengl plugin (adapter was ") << adapter << SGE_TEXT(").\n");

	bool windowed = param.windowed;
#if defined(SGE_WINDOWS_PLATFORM)
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

#elif defined(SGE_HAVE_X11)
	const int screen = XDefaultScreen(dsp->get());

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
		wnd.reset(
			new x_window(
				window::window_pos(0,0),
				window::window_size(param.mode.width(), param.mode.height()),
				string(),
				dsp,
				swa,
				visual->visual_info()));

	if(!windowed)
		XMapWindow(dsp->get(), wnd->get_window());
	else
		XMapRaised(dsp->get(), wnd->get_window());

	current.reset(new glx_current(dsp, *wnd, context));

 	con_manager.scoped_connect(
		wnd->register_callback(
			MapNotify,
			boost::bind(&device::reset_viewport_on_map, this, _1)));
	con_manager.scoped_connect(
		wnd->register_callback(
			ConfigureNotify,
			boost::bind(&device::reset_viewport_on_configure, this, _1)));

	XSync(dsp->get(), False);
#endif
	if(glewInit() != GLEW_OK)
		throw exception(SGE_TEXT("glewInit() failed!"));

	initialize_vbo();
	initialize_pbo();

	// FIXME:
	//set_target(renderer::default_target);
	set_state(renderer::default_states());
}

void sge::ogl::device::begin_rendering()
{
	SGE_OPENGL_SENTRY

	glClear(
		get_clear_bit(renderer::bool_state::clear_backbuffer)
		| get_clear_bit(renderer::bool_state::clear_zbuffer)
		| get_clear_bit(renderer::bool_state::clear_stencil));
}

sge::renderer::index_buffer_ptr const
sge::ogl::device::create_index_buffer(
	renderer::index_format::type const format,
	renderer::index_buffer::size_type const sz,
	renderer::index_buffer::resource_flag_type const flags)
{
	return renderer::index_buffer_ptr(
		new index_buffer(
			format,
			sz,
			flags));
}

const sge::ogl::fbo_target_ptr
sge::ogl::device::create_render_target(
	const renderer::target::dim_type& dim)
{
	return fbo_target_ptr(
		new fbo_target(dim));
}

sge::renderer::texture_ptr const
sge::ogl::device::create_texture(
	renderer::texture::dim_type const &dim,
	renderer::color_format::type const format,
	renderer::filter_args const &filter,
	renderer::texture::resource_flag_type const flags)
{
	return renderer::texture_ptr(
		new texture(
			dim,
			format,
			filter,
			flags));
}

sge::renderer::vertex_buffer_ptr const
sge::ogl::device::create_vertex_buffer(
	renderer::vertex_format const &format,
	renderer::vertex_buffer::size_type const sz,
	renderer::vertex_buffer::resource_flag_type const flags)
{
	return renderer::vertex_buffer_ptr(
		new vertex_buffer(
			format,
			sz,
			flags));
}

#if 0
const sge::renderer::volume_texture_ptr
sge::ogl::device::create_volume_texture(
	renderer::volume_texture::image_view_array const &src,
	const renderer::filter_args& filter,
	const renderer::volume_texture::resource_flag_type flags)
{
	/*return renderer::volume_texture_ptr(
		new volume_texture(
			src,
			filter,
			flags));*/
}
#endif

sge::renderer::cube_texture_ptr const
sge::ogl::device::create_cube_texture(
	renderer::cube_texture::size_type const border_size,
	renderer::color_format::type const format,
	const renderer::filter_args& filter,
	const renderer::cube_texture::resource_flag_type flags)
{

}

void sge::ogl::device::end_rendering()
{
#if defined(SGE_HAVE_X11)
	SGE_OPENGL_SENTRY
	glXSwapBuffers(dsp->get(), wnd->get_window());
#elif defined(SGE_WINDOWS_PLATFORM)
	if(wglSwapLayerBuffers(hdc->hdc(), WGL_SWAP_MAIN_PLANE) == FALSE)
		throw exception(SGE_TEXT("wglSwapLayerBuffers() failed!"));
#endif
}

const sge::renderer::caps& sge::ogl::device::get_caps() const
{
	return caps_;
}

const sge::window_ptr sge::ogl::device::get_window() const
{
	return wnd;
}

const sge::renderer::screen_size_t
sge::ogl::device::screen_size() const
{
	return param.mode.size;
}

void sge::ogl::device::render(
	const renderer::vertex_buffer_ptr vb,
	const renderer::index_buffer_ptr ib,
	const renderer::vertex_buffer::size_type first_vertex,
	const renderer::vertex_buffer::size_type num_vertices,
	const renderer::indexed_primitive_type::type ptype,
	const renderer::index_buffer::size_type pcount,
	const renderer::index_buffer::size_type first_index)
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
		static_cast<GLsizei>(
			renderer::indices_per_primitive(ptype) * pcount),
		gl_ib.format(),
		gl_ib.buffer_offset(
			first_index));
}

void sge::ogl::device::render(
	const renderer::vertex_buffer_ptr vb,
	const renderer::vertex_buffer::size_type first_vertex,
	const renderer::vertex_buffer::size_type num_vertices,
	const renderer::nonindexed_primitive_type::type ptype)
{
	if(!vb)
		throw exception(SGE_TEXT("vb may not be 0 for renderer::render!"));

	SGE_OPENGL_SENTRY

	set_vertex_buffer(vb);
	set_index_buffer(renderer::index_buffer_ptr());

	const GLenum prim_type = convert_cast(ptype);

	glDrawArrays(prim_type,
	             static_cast<GLsizei>(first_vertex),
	             static_cast<GLint>(num_vertices));

}

void sge::ogl::device::set_state(
	const renderer::state_list &states)
{
	const state_visitor visitor(*this);
	BOOST_FOREACH(const renderer::any_state& s, states.get())
	{
		boost::apply_visitor(visitor, s);
		current_states.overwrite(s);
	}
}

void sge::ogl::device::push_state(
	const renderer::state_list& states)
{
	renderer::state_list list;
	BOOST_FOREACH(const renderer::any_state& s, states.get())
		list.overwrite(get_any_state(s));
	
	state_levels.push(list);
	set_state(states);
}

void sge::ogl::device::set_stencil_func()
{
	SGE_OPENGL_SENTRY
	glStencilFunc(
		convert_cast(get_state(renderer::stencil_func::off)), // FIXME
		0,
		0); // FIXME
}

void sge::ogl::device::set_blend_func()
{
	SGE_OPENGL_SENTRY
	glBlendFunc(
		convert_cast(get_state(renderer::source_blend_func::zero)), // FIXME
		convert_cast(get_state(renderer::dest_blend_func::zero))); // FIXME
}

GLenum sge::ogl::device::get_clear_bit(
	const renderer::bool_state::type s) const
{
	return get_state(s).value() ? convert_clear_bit(s) : 0;
}

template<typename T>
T sge::ogl::device::get_state(const T& t) const
{
	renderer::state_list::set_type const &states(current_states.get());
	const renderer::state_list::set_type::const_iterator it = states.find(t);
	if(it == states.end())
		throw exception(SGE_TEXT("ogl::device::get_state(): state not found!"));
	return boost::get<T>(*it);
}

const sge::renderer::any_state&
sge::ogl::device::get_any_state(
	const renderer::any_state& state) const
{
	renderer::state_list::set_type const &states(current_states.get());
	const renderer::state_list::set_type::const_iterator it = states.find(state);
	if(it == states.end())
		throw exception(SGE_TEXT("ogl::device::get_any_state(): state not found!"));
	return *it;
}

void sge::ogl::device::set_material(const renderer::material& mat)
{
	SGE_OPENGL_SENTRY

	const GLenum face = GL_FRONT_AND_BACK;
	// FIXME: UB
	//glMaterialfv(face, GL_AMBIENT, reinterpret_cast<const GLfloat*>(&mat.ambient));
	//glMaterialfv(face, GL_DIFFUSE, reinterpret_cast<const GLfloat*>(&mat.diffuse));
	//glMaterialfv(face, GL_SPECULAR, reinterpret_cast<const GLfloat*>(&mat.specular));
	//glMaterialfv(face, GL_EMISSION, reinterpret_cast<const GLfloat*>(&mat.emissive));
	glMaterialf(face, GL_SHININESS, mat.power);
}

void sge::ogl::device::set_viewport(
	const renderer::viewport& v)
{
	SGE_OPENGL_SENTRY
	glViewport(v.x, v.y, v.w, v.h);
}

#ifdef SGE_HAVE_X11
void sge::ogl::device::reset_viewport_on_map(const XEvent&)
{
	center_viewport(wnd->width(), wnd->height());
}

void sge::ogl::device::reset_viewport_on_configure(const XEvent& e)
{
	const XConfigureEvent& r(e.xconfigure);
	center_viewport(r.width, r.height);
}

void sge::ogl::device::center_viewport(const int w, const int h)
{
	const renderer::pixel_unit screen_w =
		static_cast<renderer::pixel_unit>(screen_width()),
		         screen_h =
		static_cast<renderer::pixel_unit>(screen_height()),
	                 x =
		w > screen_w
		? (w - screen_w) / 2
		: 0,
	                 y =
		h > screen_h
		? (h - screen_h) / 2
		: 0;

	set_viewport(renderer::viewport(x, y, screen_width(), screen_height()));
}
#endif

void sge::ogl::device::transform(const math::space_matrix& matrix)
{
	SGE_OPENGL_SENTRY
	// TODO: put this in an own file!
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(math::transpose(matrix).data());
}

void sge::ogl::device::projection(const math::space_matrix& matrix)
{
	SGE_OPENGL_SENTRY

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(math::transpose(matrix).data());
}

void sge::ogl::device::set_render_target(
	const renderer::texture_ptr target)
{
	if(!target)
	{
		render_target_.reset(
			new default_target(
				math::structure_cast<
					target::dim_type::value_type>(
						screen_size())));
		render_target_->bind_me();
		const window::window_pos offset = wnd->viewport_offset();
		set_viewport(
			// TODO: better ctor for viewport
			renderer::viewport(
				offset.x(),
				offset.y(),
				wnd->width(),
				wnd->height()));
		return;
	}

	const shared_ptr<texture> p(dynamic_pointer_cast<texture>(target));
	const fbo_target_ptr ntarget = create_render_target(p->dim());
	render_target_ = ntarget;
	ntarget->bind_texture(p);
	set_viewport(
		renderer::viewport(
			0,
			0,
			static_cast<renderer::screen_unit>(p->dim().w()),
			static_cast<renderer::screen_unit>(p->dim().h())));
}

sge::renderer::const_target_ptr const
sge::ogl::device::get_target() const
{
	return render_target_;
}

void sge::ogl::device::set_texture(
	const renderer::texture_base_ptr tex,
	const renderer::stage_type stage)
{
	set_texture_level(stage);

	disable(GL_TEXTURE_1D);
	disable(GL_TEXTURE_2D);
	// FIXME:
	//disable(detail::volume_texture_type);
	disable_cube_texture();

	if(!tex)
		return;
	texture_base& b = dynamic_cast<texture_base&>(*tex);
	enable(b.type());
	b.bind_me();
}

void sge::ogl::device::enable_light(
	const renderer::light_index index,
	const bool enable_)
{
	const GLenum glindex = convert_light_index(index);
	enable(glindex, enable_);
}

void sge::ogl::device::set_light(
	const renderer::light_index index,
	const renderer::light& l)
{
	const GLenum glindex = convert_light_index(index);

	set_light_colorf(glindex, GL_AMBIENT, l.ambient);
	set_light_colorf(glindex, GL_DIFFUSE, l.diffuse);
	set_light_colorf(glindex, GL_SPECULAR, l.specular);

	const math::vector4 pos(l.pos, static_cast<math::vector4::value_type>(1));
	set_light_pos(glindex, pos);

	set_light_dir(glindex, l.dir);

	set_light_float(glindex, GL_CONSTANT_ATTENUATION, l.const_attenuation);
	set_light_float(glindex, GL_LINEAR_ATTENUATION, l.linear_attenuation);
	set_light_float(glindex, GL_QUADRATIC_ATTENUATION, l.quadratic_attenuation);

	set_light_float(glindex, GL_SPOT_EXPONENT, l.distribution_exponent);
	set_light_float(glindex, GL_SPOT_CUTOFF, l.cutoff_angle);
}

void sge::ogl::device::set_texture_stage_op(
	const renderer::stage_type stage,
	const renderer::texture_stage_op::type op,
	const renderer::texture_stage_op_value::type value)
{
	set_texture_stage(stage, op, value);
	set_texture_stage_scale(value);
}

void sge::ogl::device::set_texture_stage_arg(
	const renderer::stage_type stage,
	const renderer::texture_stage_arg::type arg,
	const renderer::texture_stage_arg_value::type value)
{
	set_texture_stage(stage, arg, value);
}

void sge::ogl::device::pop_level()
{
	state_levels.pop();
}

const sge::renderer::glsl::program_ptr
sge::ogl::device::create_glsl_program(
	const std::string& vs_source,
	const std::string& ps_source)
{
	return glsl::create_program_impl(vs_source, ps_source);
}

void sge::ogl::device::set_glsl_program(
	const renderer::glsl::program_ptr prog)
{
	glsl::set_program_impl(prog);
}

void sge::ogl::device::set_vertex_buffer(const renderer::vertex_buffer_ptr vb)
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

void sge::ogl::device::set_index_buffer(const renderer::index_buffer_ptr ib)
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
