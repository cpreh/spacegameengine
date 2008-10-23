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
#include "../matrix.hpp"
#include "../split_states.hpp"
#include "../material.hpp"
#include "../glew.hpp"
#if defined(SGE_WINDOWS_PLATFORM)
#include <sge/windows/windows.hpp>
#include <sge/windows/window.hpp>
#elif defined(SGE_HAVE_X11)
#include <sge/x11/window.hpp>
#include <sge/x11/display.hpp>
#include <sge/x11/visual.hpp>
#include <boost/bind.hpp>
#else
#error "Implement me!"
#endif
#include <sge/bit.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/primitive.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/light.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <sge/math/matrix_impl.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <sstream>

// TODO: maybe support different adapters?
sge::ogl::device::device(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window_ptr const wnd_param)
 : param(param),
   current_states(renderer::state::default_())
{
//	if(adapter > 0)
//		sge::cerr << SGE_TEXT("stub: adapter cannot be > 0 for opengl plugin (adapter was ") << adapter << SGE_TEXT(").\n");

	bool windowed = true; // param.windowed;
#if defined(SGE_WINDOWS_PLATFORM)
	if(!windowed)
	{
		DEVMODE settings;
		memset(&settings,0,sizeof(DEVMODE));
		settings.dmSize = sizeof(DEVMODE);
		settings.dmPelsWidth    = param.mode().width();
		settings.dmPelsHeight   = param.mode().height();
		settings.dmBitsPerPel   = static_cast<UINT>(param.mode().depth);
		settings.dmDisplayFrequency = param.mode().refresh_rate;
		settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH|DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
		if(ChangeDisplaySettings(&settings,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			//sge::cerr << SGE_TEXT("Cannot change resolution to ") << param.mode << SGE_TEXT("! Reverting to window mode!\n");
			windowed = false;
		}
	}

	wnd = polymorphic_pointer_cast<windows::window>(wnd_param);

	hdc.reset(
		new windows::gdi_device(
			wnd->hwnd(),
			windows::gdi_device::get_tag()));

	context.reset(
		new wgl::context(
			*hdc));

	current.reset(
		new wgl::current(
			*hdc,
			*context));

#elif defined(SGE_HAVE_X11)
	wnd = polymorphic_pointer_cast<x11::window>(wnd_param);

	x11::display_ptr const dsp(
		wnd->display());

	if(!windowed)
	{
		modes.reset(
			new x11::xf86_vidmode_array(
				dsp,
				dsp->default_screen()));
		resolution = modes->switch_to_mode(param.mode());
		if(!resolution)
		{
			//sge::cerr << SGE_TEXT("Warning: No resolution matches against ") << param.mode << SGE_TEXT("! Falling back to window mode!\n");
			windowed = true;
		}
	}

	x11::const_visual_ptr const visual(
		wnd->visual());

	context.reset(new glx::context(dsp, visual->info()));

	if(!windowed)
		wnd->map();
	else
		wnd->map_raised();

	current.reset(new glx::current(dsp, *wnd, context));

 	con_manager.connect(
		wnd->register_callback(
			MapNotify,
			boost::bind(&device::reset_viewport_on_map, this, _1)));
	con_manager.connect(
		wnd->register_callback(
			ConfigureNotify,
			boost::bind(&device::reset_viewport_on_configure, this, _1)));
	
	dsp->sync();
#endif
	initialize_glew();

	initialize_vbo();
	initialize_pbo();

	set_state(
		renderer::state::default_());
	
	set_render_target(
		default_render_target);
}

void sge::ogl::device::begin_rendering()
{
	SGE_OPENGL_SENTRY

	glClear(
		get_clear_bit(renderer::state::bool_::clear_backbuffer)
		| get_clear_bit(renderer::state::bool_::clear_zbuffer)
		| get_clear_bit(renderer::state::bool_::clear_stencil));
}

sge::renderer::index_buffer_ptr const
sge::ogl::device::create_index_buffer(
	renderer::index_format::type const format,
	renderer::size_type const sz,
	renderer::resource_flag_t const flags)
{
	return renderer::index_buffer_ptr(
		new index_buffer(
			format,
			sz,
			flags));
}

sge::ogl::fbo_target_ptr const
sge::ogl::device::create_render_target()
{
	return fbo_target_ptr(
		new fbo_target());
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
	renderer::vf::dynamic_format const &format,
	renderer::size_type const sz,
	renderer::resource_flag_t const flags)
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
	renderer::size_type const border_size,
	renderer::color_format::type const format,
	renderer::filter_args const &filter,
	renderer::resource_flag_t const flags)
{
	return renderer::cube_texture_ptr(
		new cube_texture(
			border_size,
			format,
			filter,
			flags));
}

void sge::ogl::device::end_rendering()
{
#if defined(SGE_HAVE_X11)
	SGE_OPENGL_SENTRY
	glXSwapBuffers(
		wnd->display()->get(),
		wnd->get_window());
#elif defined(SGE_WINDOWS_PLATFORM)
	if(wglSwapLayerBuffers(hdc->hdc(), WGL_SWAP_MAIN_PLANE) == FALSE)
		throw exception(SGE_TEXT("wglSwapLayerBuffers() failed!"));
#endif
}

sge::renderer::caps const
sge::ogl::device::get_caps() const
{
	return renderer::caps(
		0,
		SGE_TEXT("fixme"),
		SGE_TEXT("fixme"),
		1024,
		0); // FIXME
}

sge::window_ptr const
sge::ogl::device::get_window() const
{
	return wnd;
}

sge::renderer::screen_size_t const
sge::ogl::device::screen_size() const
{
	return param.mode().size;
}

void sge::ogl::device::render(
	renderer::const_vertex_buffer_ptr const vb,
	renderer::const_index_buffer_ptr const ib,
	renderer::size_type const first_vertex,
	renderer::size_type const num_vertices,
	renderer::indexed_primitive_type::type const ptype,
	renderer::size_type const pcount,
	renderer::size_type const first_index)
{
	if(!vb)
		throw exception(
			SGE_TEXT("vb may not be 0 for renderer::render!"));
	if(!ib)
		throw exception(
			SGE_TEXT("ib may not be 0 for renderer::render for indexed primitives!"));

	set_vertex_buffer(vb);
	set_index_buffer(ib);

	GLenum const prim_type = convert_cast(ptype);

	index_buffer const &gl_ib = dynamic_cast<index_buffer const &>(*ib);

	SGE_OPENGL_SENTRY

	glDrawElements(
		prim_type,
		static_cast<GLsizei>(
			renderer::indices_per_primitive(ptype) * pcount),
		gl_ib.format(),
		gl_ib.buffer_offset(
			first_index));
}

void sge::ogl::device::render(
	renderer::const_vertex_buffer_ptr const vb,
	renderer::size_type const first_vertex,
	renderer::size_type const num_vertices,
	renderer::nonindexed_primitive_type::type const ptype)
{
	if(!vb)
		throw exception(
			SGE_TEXT("vb may not be 0 for renderer::render!"));

	set_vertex_buffer(vb);

	GLenum const prim_type = convert_cast(ptype);

	SGE_OPENGL_SENTRY

	glDrawArrays(
		prim_type,
		static_cast<GLsizei>(first_vertex),
		static_cast<GLint>(num_vertices));
}

void sge::ogl::device::set_state(
	renderer::state::list const &states)
{
	split_states split(current_states);
	state_visitor const visitor(split);
	BOOST_FOREACH(renderer::state::any const &s, states.values())
	{
		current_states.overwrite(s);
		boost::apply_visitor(visitor, s);
	}
}

void sge::ogl::device::push_state(
	renderer::state::list const &states)
{	
	state_levels.push(
		current_states);

	set_state(
		renderer::state::combine(
			current_states,
			states));
}

void sge::ogl::device::pop_state()
{
	set_state(state_levels.top());
	state_levels.pop();
}

GLenum sge::ogl::device::get_clear_bit(
	renderer::state::bool_::trampoline_type const &s) const
{
	return current_states.get(s) ? convert_clear_bit(s) : 0;
}

void sge::ogl::device::set_material(
	renderer::material const &mat)
{
	ogl::set_material(mat);
}

void sge::ogl::device::set_viewport(
	renderer::viewport const &v)
{
	SGE_OPENGL_SENTRY
	glViewport(
		v.pos().x(),
		v.pos().y(),
		v.size().w(),
		v.size().h());
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
		static_cast<renderer::pixel_unit>(screen_size().w()),
		         screen_h =
		static_cast<renderer::pixel_unit>(screen_size().h()),
	                 x =
		w > screen_w
		? (w - screen_w) / 2
		: 0,
	                 y =
		h > screen_h
		? (h - screen_h) / 2
		: 0;

	set_viewport(
		renderer::viewport(
			renderer::pixel_pos_t(
				x, y),
			screen_size()));
}
#endif

void sge::ogl::device::transform(
	math::space_matrix const &matrix)
{
	set_matrix(
		GL_MODELVIEW,
		matrix);
}

void sge::ogl::device::projection(
	math::space_matrix const &matrix)
{
	set_matrix(
		GL_PROJECTION,
		matrix);
}

void sge::ogl::device::texture_transform(
	math::space_matrix const &matrix)
{
	set_matrix(
		GL_TEXTURE,
		matrix);
}

void sge::ogl::device::set_render_target(
	renderer::texture_ptr const target)
{
	if(!target)
	{
		render_target_.reset(
			new default_target(
				math::structure_cast<
					target::dim_type::value_type>(
						screen_size()),
				param.mode().depth));
		render_target_->bind_me();
		window::window_pos const offset = wnd->viewport_offset();
		set_viewport(
			renderer::viewport(
				offset,
				wnd->size()));
		return;
	}

	shared_ptr<texture> const p(
		dynamic_pointer_cast<texture>(target));
	
	fbo_target_ptr const ntarget = create_render_target();

	ntarget->bind_texture(p);

	set_viewport(
		renderer::viewport(
			renderer::pixel_pos_t(0, 0),
			math::structure_cast<renderer::screen_unit>(
				p->dim())));
	
	render_target_ = ntarget;
}

sge::renderer::const_target_ptr const
sge::ogl::device::get_target() const
{
	return render_target_;
}

void sge::ogl::device::set_texture(
	renderer::const_texture_base_ptr const tex,
	renderer::stage_type const stage)
{
	set_texture_level(stage);

	disable(GL_TEXTURE_1D);
	disable(GL_TEXTURE_2D);
	//disable(detail::volume_texture_type);
	disable_cube_texture();

	if(!tex)
		return;
	texture_base const &b = dynamic_cast<texture_base const &>(*tex);
	enable(b.type());
	b.bind_me();
}

void sge::ogl::device::enable_light(
	renderer::light_index const index,
	bool const enable_)
{
	GLenum const glindex = convert_light_index(index);
	enable(glindex, enable_);
}

void sge::ogl::device::set_light(
	renderer::light_index const index,
	renderer::light const &l)
{
	GLenum const glindex = convert_light_index(index);

	set_light_color(glindex, GL_AMBIENT, l.ambient);
	set_light_color(glindex, GL_DIFFUSE, l.diffuse);
	set_light_color(glindex, GL_SPECULAR, l.specular);

	math::vector4 const pos(l.pos, static_cast<math::vector4::value_type>(1));
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

sge::renderer::glsl::program_ptr const
sge::ogl::device::create_glsl_program(
	renderer::glsl::string const &vs_source,
	renderer::glsl::string const &ps_source)
{
	return glsl::create_program_impl(
		vs_source,
		ps_source);
}

sge::renderer::glsl::program_ptr const
sge::ogl::device::create_glsl_program(
	renderer::glsl::istream &vs_source,
	renderer::glsl::istream &ps_source)
{
	// unfortunately opengl can't read out of files directly
	typedef std::basic_ostringstream<
		renderer::glsl::char_type
	> osstream;

	osstream vs_stream,
	         ps_stream;
	vs_stream << vs_source.rdbuf();
	ps_stream << ps_source.rdbuf();

	return create_glsl_program(
		vs_stream.str(),
		ps_stream.str());
}

void sge::ogl::device::set_glsl_program(
	const renderer::glsl::program_ptr prog)
{
	glsl::set_program_impl(prog);
}

void sge::ogl::device::set_vertex_buffer(
	renderer::const_vertex_buffer_ptr const vb)
{
	vertex_buffer const &ovb = dynamic_cast<vertex_buffer const &>(*vb);
	ovb.set_format();
}

void sge::ogl::device::set_index_buffer(
	renderer::const_index_buffer_ptr const ib)
{
	index_buffer const &oib = dynamic_cast<index_buffer const &>(*ib);
	oib.bind_me();
}
