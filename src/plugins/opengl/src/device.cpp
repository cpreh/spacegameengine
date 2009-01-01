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


#include <boost/foreach.hpp>
#include "../device.hpp"
#include "../vertex_buffer.hpp"
#include "../index_buffer.hpp"
#include "../vertex_buffer.hpp"
#include "../texture.hpp"
#include "../cube_texture.hpp"
#include "../volume_texture.hpp"
#include "../convert_clear_bit.hpp"
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
#include "../fbo_target.hpp"
#include "../convert_primitive.hpp"
#include "../fbo_projection.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/primitive.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/math/matrix_util.hpp>
#include <sge/window/instance.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/bind.hpp>
#include <sstream>

sge::ogl::device::device(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd)
:
	param(param),
	wnd(wnd),
	current_states(
		renderer::state::default_()),
	state_(
		param,
		adapter,
		wnd,
		boost::bind(
			&device::viewport,
			this,
			_1)),
	fbo_active(
		false),
	projection_(
		math::matrix_identity<float>())

{
	initialize_glew();

	initialize_vbo();
	initialize_pbo();

	state(
		renderer::state::default_());
	
	target(
		default_target);
	
	projection_internal();
}

void sge::ogl::device::begin_rendering()
{
	SGE_OPENGL_SENTRY

	glClear(
		clear_bit(renderer::state::bool_::clear_backbuffer)
		| clear_bit(renderer::state::bool_::clear_zbuffer)
		| clear_bit(renderer::state::bool_::clear_stencil));
}

sge::renderer::index_buffer_ptr const
sge::ogl::device::create_index_buffer(
	renderer::index_format::type const format,
	renderer::size_type const sz,
	renderer::resource_flag_t const flags)
{
	return renderer::index_buffer_ptr(
		new ogl::index_buffer(
			format,
			sz,
			flags));
}

sge::renderer::texture_ptr const
sge::ogl::device::create_texture(
	renderer::texture::dim_type const &dim,
	renderer::color_format::type const format,
	renderer::texture_filter const &filter,
	renderer::texture::resource_flag_type const flags)
{
	return renderer::texture_ptr(
		new ogl::texture(
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
		new ogl::vertex_buffer(
			format,
			sz,
			flags));
}

#if 0
const sge::renderer::volume_texture_ptr
sge::ogl::device::create_volume_texture(
	renderer::volume_texture::image_view_array const &src,
	const renderer::texture_filter& filter,
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
	renderer::texture_filter const &filter,
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
	state_.swap_buffers();
}

sge::renderer::device::caps_t const
sge::ogl::device::caps() const
{
	return renderer::caps(
		0,
		SGE_TEXT("fixme"),
		SGE_TEXT("fixme"),
		1024,
		0); // FIXME
}

sge::window::instance_ptr const
sge::ogl::device::window() const
{
	return wnd;
}

sge::renderer::screen_size_t const
sge::ogl::device::screen_size() const
{
	return param.mode().size();
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

	vertex_buffer(vb);
	index_buffer(ib);

	GLenum const prim_type = convert_primitive(ptype);

	ogl::index_buffer const &
		gl_ib = dynamic_cast<ogl::index_buffer const &>(
			*ib);

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

	vertex_buffer(vb);

	GLenum const prim_type = convert_primitive(ptype);

	SGE_OPENGL_SENTRY

	glDrawArrays(
		prim_type,
		static_cast<GLsizei>(first_vertex),
		static_cast<GLint>(num_vertices));
}

void sge::ogl::device::state(
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

	state(
		renderer::state::combine(
			current_states,
			states));
}

void sge::ogl::device::pop_state()
{
	state(state_levels.top());
	state_levels.pop();
}

GLenum sge::ogl::device::clear_bit(
	renderer::state::bool_::trampoline_type const &s) const
{
	return current_states.get(s) ? convert_clear_bit(s) : 0;
}

void sge::ogl::device::material(
	renderer::material const &mat)
{
	ogl::set_material(mat);
}

void sge::ogl::device::viewport(
	renderer::viewport const &v)
{
	SGE_OPENGL_SENTRY
	glViewport(
		v.pos().x(),
		v.pos().y(),
		v.size().w(),
		v.size().h());
}

void sge::ogl::device::transform(
	renderer::any_matrix const &matrix)
{
	set_matrix(
		GL_MODELVIEW,
		matrix);
}

void sge::ogl::device::projection(
	renderer::any_matrix const &matrix)
{
	projection_ = matrix;
	projection_internal();
//	set_matrix(
//		GL_PROJECTION,
//		matrix);
}

void sge::ogl::device::texture_transform(
	renderer::any_matrix const &matrix)
{
	set_matrix(
		GL_TEXTURE,
		matrix);
}

void sge::ogl::device::target(
	renderer::texture_ptr const ntarget)
{
	if(!ntarget)
	{
		target_.reset(
			new ogl::default_target(
				math::structure_cast<
					target::dim_type::value_type>(
						screen_size()),
				param.mode().bit_depth()));
		target_->bind_me();
		state_.reset_viewport();
		fbo_active = false;
		projection_internal();
		return;
	}

	shared_ptr<ogl::texture> const p(
		dynamic_pointer_cast<ogl::texture>(
			ntarget));
	
	fbo_target_ptr const ftarget = create_target();

	ftarget->bind_texture(p);

	viewport(
		renderer::viewport(
			renderer::pixel_pos_t(0, 0),
			math::structure_cast<renderer::screen_unit>(
				p->dim())));
	
	target_ = ftarget;
	fbo_active = true;
	projection_internal();
}

sge::renderer::const_target_ptr const
sge::ogl::device::target() const
{
	return target_;
}

void sge::ogl::device::texture(
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

void sge::ogl::device::light(
	renderer::light_index const index,
	renderer::light const &l)
{
	ogl::set_light(
		index,
		l);
}

void sge::ogl::device::texture_stage_op(
	renderer::stage_type const stage,
	renderer::texture_stage_op::type const op,
	renderer::texture_stage_op_value::type const value)
{
	set_texture_stage(stage, op, value);
	set_texture_stage_scale(value);
}

void sge::ogl::device::texture_stage_arg(
	renderer::stage_type const stage,
	renderer::texture_stage_arg::type const arg,
	renderer::texture_stage_arg_value::type const value)
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

void sge::ogl::device::glsl_program(
	renderer::glsl::program_ptr const prog)
{
	glsl::set_program_impl(prog);
}

void sge::ogl::device::vertex_buffer(
	renderer::const_vertex_buffer_ptr const vb)
{
	ogl::vertex_buffer const &
		ovb = dynamic_cast<ogl::vertex_buffer const &>(
			*vb);
	ovb.set_format();
}

void sge::ogl::device::index_buffer(
	renderer::const_index_buffer_ptr const ib)
{
	ogl::index_buffer const &
		oib = dynamic_cast<ogl::index_buffer const &>(
			*ib);
	oib.bind_me();
}

sge::ogl::fbo_target_ptr const
sge::ogl::device::create_target()
{
	return fbo_target_ptr(
		new fbo_target());
}

void sge::ogl::device::projection_internal()
{
	set_matrix(
		GL_PROJECTION,
		fbo_active
		? fbo_projection(
			projection_)
		: projection_);
		
}
