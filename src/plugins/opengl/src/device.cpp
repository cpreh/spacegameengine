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


#include <boost/foreach.hpp>
#include "../device.hpp"
#include "../index_buffer.hpp"
#include "../vertex_buffer.hpp"
#include "../texture.hpp"
#include "../cube_texture.hpp"
#include "../volume_texture.hpp"
#include "../default_target.hpp"
#include "../light.hpp"
#include "../enable.hpp"
#include "../enable_bool.hpp"
#include "../disable.hpp"
#include "../set_texture_level.hpp"
#include "../set_texture_stage.hpp"
#include "../set_texture_stage_scale.hpp"
#include "../check_state.hpp"
#include "../state_visitor.hpp"
#include "../glsl/set_program.hpp"
#include "../glsl/create_program.hpp"
#include "../glsl/create_vertex_shader.hpp"
#include "../glsl/create_pixel_shader.hpp"
#include "../common.hpp"
#include "../set_matrix_and_mode.hpp"
#include "../split_states.hpp"
#include "../material.hpp"
#include "../glew/initialize.hpp"
#include "../fbo_target.hpp"
#include "../fbo_projection.hpp"
#include "../viewport.hpp"
#include "../viewport_pos.hpp"
#include "../background_dim.hpp"
#include "../caps.hpp"
#include "../cube_texture_context.hpp"
#include "../context/use.hpp"
#include "../convert/clear_bit.hpp"
#include "../convert/indexed_primitive.hpp"
#include "../convert/nonindexed_primitive.hpp"
#include "../convert/light_index.hpp"
#include "../convert/matrix_mode.hpp"
#include <sge/renderer/caps.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/combine.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/window/instance.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/cstdint.hpp>
#include <sstream>

sge::opengl::device::device(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd
)
:
	param(param),
	wnd(wnd),
	current_states(
		renderer::state::default_()
	),
	state_(
		param,
		adapter,
		wnd,
		std::tr1::bind(
			&device::reset_viewport,
			this,
			std::tr1::placeholders::_1
		)
	),
	fbo_active(
		false
	),
	projection_(
		fcppt::math::matrix::static_<float, 4, 4>::type::identity()
	),
	viewport_mode_(
		renderer::viewport_mode::centered_screen_size
	),
	viewport_(
		renderer::pixel_pos::null(),
		param.display_mode().size()
	),
	default_target_(
		fcppt::make_shared_ptr<
			opengl::default_target
		>(
			fcppt::math::dim::structure_cast<
				target::dim_type
			>(
				screen_size()
			),
			param.display_mode().bit_depth()
		)
	),
	target_(
		default_target_
	),
	caps_(),
	state_levels(),
	context_()
{
	glew::initialize();

	state(
		renderer::state::default_()
	);

	projection_internal();

	reset_viewport_default();

	target_->bind_me();
}

void
sge::opengl::device::begin_rendering()
{
	glClear(
		clear_bit(renderer::state::bool_::clear_backbuffer)
		| clear_bit(renderer::state::bool_::clear_zbuffer)
		| clear_bit(renderer::state::bool_::clear_stencil)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glClear failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::device::end_rendering()
{
	state_.swap_buffers();
}

void
sge::opengl::device::render(
	renderer::const_index_buffer_ptr const ib,
	renderer::first_vertex const first_vertex,
	renderer::vertex_count const num_vertices,
	renderer::indexed_primitive_type::type const ptype,
	renderer::primitive_count const pcount,
	renderer::first_index const first_index
)
{
	if(!ib)
		throw exception(
			FCPPT_TEXT("ib may not be 0 for renderer::render for indexed primitives!")
		);

	index_buffer_base const & gl_ib(
		dynamic_cast<
			index_buffer_base const &
		>(
			*ib
		)
	);

	gl_ib.bind_me();

	glDrawElements(
		convert::indexed_primitive(
			ptype
		),
		static_cast<GLsizei>(
			renderer::indices_per_primitive(
				ptype
			) * pcount
		),
		gl_ib.gl_format(),
		gl_ib.buffer_offset(
			first_index
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDrawElements failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::device::render(
	renderer::first_vertex const first_vertex,
	renderer::vertex_count const num_vertices,
	renderer::nonindexed_primitive_type::type const ptype
)
{
	glDrawArrays(
		convert::nonindexed_primitive(
			ptype
		),
		static_cast<GLsizei>(first_vertex),
		static_cast<GLint>(num_vertices)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDrawArrays failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::device::set_vertex_buffer(
	renderer::const_vertex_buffer_ptr const vb
)
{
	dynamic_cast<
		opengl::vertex_buffer const &
	>(
		*vb
	).set_format();
}

void
sge::opengl::device::unset_vertex_buffer(
	renderer::const_vertex_buffer_ptr const vb
)
{
	dynamic_cast<
		opengl::vertex_buffer const &
	>(
		*vb
	).unset_format();
}

void
sge::opengl::device::state(
	renderer::state::list const &states
)
{
	split_states split(
		current_states
	);

	state_visitor const visitor(
		context_,
		split,
		param.depth_buffer(),
		param.stencil_buffer()
	);

	BOOST_FOREACH(
		renderer::state::any const &s,
		states.values()
	)
	{
		current_states.overwrite(s);

		fcppt::variant::apply_unary(
			visitor, s
		);
	}
}

void
sge::opengl::device::push_state(
	renderer::state::list const &states
)
{
	state_levels.push(
		current_states
	);

	state(
		renderer::state::combine(
			current_states,
			states
		)
	);
}

void
sge::opengl::device::pop_state()
{
	state(state_levels.top());
	state_levels.pop();
}

void
sge::opengl::device::material(
	renderer::material const &mat
)
{
	opengl::set_material(
		mat
	);
}

void
sge::opengl::device::enable_light(
	renderer::light_index const index,
	bool const enable_
)
{
	opengl::enable_bool(
		convert::light_index(
			index
		),
		enable_
	);
}

void
sge::opengl::device::light(
	renderer::light_index const index,
	renderer::light const &l
)
{
	opengl::set_light(
		index,
		l
	);
}

void
sge::opengl::device::texture_stage_op(
	renderer::stage_type const stage,
	renderer::texture_stage_op::type const op,
	renderer::texture_stage_op_value::type const value
)
{
	opengl::set_texture_stage(
		context_,
		stage,
		op,
		value
	);

	opengl::set_texture_stage_scale(
		value
	);
}

void
sge::opengl::device::texture_stage_arg(
	renderer::stage_type const stage,
	renderer::texture_stage_arg::type const arg,
	renderer::texture_stage_arg_value::type const value
)
{
	opengl::set_texture_stage(
		context_,
		stage,
		arg,
		value
	);
}

void
sge::opengl::device::texture(
	renderer::const_texture_base_ptr const tex,
	renderer::stage_type const stage
)
{
	opengl::set_texture_level(
		context_,
		stage
	);

	// TODO: we should keep track of what is enabled and what isn't!
	disable(GL_TEXTURE_1D);
	disable(GL_TEXTURE_2D);
	//disable(detail::volume_texture_type);
	{
		cube_texture_context &cube_texture_context_(
			context::use<
				cube_texture_context
			>(
				context_
			)
		);

		if(
			cube_texture_context_.have_cube_texture()
		)
			disable(
				cube_texture_context_.cube_texture_type()
			);
	}

	if(!tex)
		return;
	
	texture_base const &b(
		dynamic_cast<
			texture_base const &
		>(
			*tex
		)
	);

	enable(b.type());

	b.bind_me();
}

void
sge::opengl::device::transform(
	renderer::matrix_mode::type const mode,
	renderer::any_matrix const &matrix
)
{
	if(
		mode == renderer::matrix_mode::projection
	)
	{
		// TODO: what can we do about this?
		projection_ = matrix;

		projection_internal();
	}
	else
		opengl::set_matrix_and_mode(
			context_,
			convert::matrix_mode(
				mode
			),
			matrix
		);
}

void
sge::opengl::device::target(
	renderer::texture_ptr const ntarget
)
{
	if(!ntarget)
	{
		target_ = default_target_;
		target_->bind_me();
		fbo_active = false;
		projection_internal();
		reset_viewport_default();
		return;
	}

	fcppt::shared_ptr<
		opengl::texture
	> const p(
		fcppt::dynamic_pointer_cast<opengl::texture>(
			ntarget
		)
	);

	fbo_target_ptr const ftarget = create_target();

	ftarget->bind_texture(p);

	target_ = ftarget;
	fbo_active = true;

	viewport(
		renderer::viewport(
			renderer::pixel_pos::null(),
			fcppt::math::dim::structure_cast<
				renderer::screen_size
			>(
				p->dim()
			)
		)
	);

	projection_internal();
}

void
sge::opengl::device::viewport(
	renderer::viewport const &v
)
{
	viewport_ = v;

	if(fbo_active)
		opengl::viewport(
			v,
			static_cast<
				renderer::screen_unit
			>(
				target_->dim().h()
			)
		);
	else
		reset_viewport_default();
}

void
sge::opengl::device::viewport_mode(
	renderer::viewport_mode::type const mode
)
{
	viewport_mode_ = mode;
}

sge::renderer::glsl::program_ptr const
sge::opengl::device::create_glsl_program()
{
	return
		glsl::create_program(
			context_
		);
}

sge::renderer::glsl::vertex_shader_ptr const
sge::opengl::device::create_glsl_vertex_shader(
	renderer::glsl::string const &_source
)
{
	return
		glsl::create_vertex_shader(
			context_,
			_source
		);
}

sge::renderer::glsl::pixel_shader_ptr const
sge::opengl::device::create_glsl_pixel_shader(
	renderer::glsl::string const &_source
)
{
	return
		glsl::create_pixel_shader(
			context_,
			_source
		);
}

void
sge::opengl::device::glsl_program(
	renderer::glsl::program_ptr const prog
)
{
	glsl::set_program(
		context_,
		prog
	);
}

sge::renderer::const_target_ptr const
sge::opengl::device::target() const
{
	return target_;
}

sge::renderer::texture_ptr const
sge::opengl::device::create_texture(
	renderer::texture::dim_type const &dim,
	image::color::format::type const format,
	renderer::filter::texture const &filter,
	renderer::resource_flags_field const &flags
)
{
	return renderer::texture_ptr(
		fcppt::make_shared_ptr<
			opengl::texture
		>(
			std::tr1::ref(
				context_
			),
			dim,
			format,
			filter,
			flags
		)
	);
}

sge::renderer::cube_texture_ptr const
sge::opengl::device::create_cube_texture(
	renderer::size_type const border_size,
	image::color::format::type const format,
	renderer::filter::texture const &filter,
	renderer::resource_flags_field const &flags
)
{
	return renderer::cube_texture_ptr(
		fcppt::make_shared_ptr<
			cube_texture
		>(
			std::tr1::ref(
				context_
			),
			border_size,
			format,
			filter,
			flags
		)
	);
}

sge::renderer::vertex_buffer_ptr const
sge::opengl::device::create_vertex_buffer(
	renderer::vf::dynamic::format const &format,
	renderer::size_type const sz,
	renderer::resource_flags_field const &flags
)
{
	return renderer::vertex_buffer_ptr(
		fcppt::make_shared_ptr<
			opengl::vertex_buffer
		>(
			std::tr1::ref(
				context_
			),
			format,
			sz,
			flags
		)
	);
}

sge::renderer::index_buffer_ptr const
sge::opengl::device::create_index_buffer(
	renderer::index::dynamic::format::type const format,
	renderer::size_type const sz,
	renderer::resource_flags_field const &flags
)
{
	switch(format)
	{
	case renderer::index::dynamic::format::i16:
		return renderer::index_buffer_ptr(
			fcppt::make_shared_ptr<
				opengl::index_buffer<
					sge::renderer::index::i16
				>
			>(
				std::tr1::ref(
					context_
				),
				sz,
				flags
			)
		);
	case renderer::index::dynamic::format::i32:
		return renderer::index_buffer_ptr(
			fcppt::make_shared_ptr<
				opengl::index_buffer<
					sge::renderer::index::i32
				>
			>(
				std::tr1::ref(
					context_
				),
				sz,
				flags
			)
		);
	}

	throw exception(
		FCPPT_TEXT("Invalid index::format!")
	);
}

#if 0
const sge::renderer::volume_texture_ptr
sge::opengl::device::create_volume_texture(
	renderer::volume_texture::image_view_array const &src,
	const renderer::texture_filter& filter,
	const renderer::volume_texture::resource_flag_type flags)
{
	/*return renderer::volume_texture_ptr(
		fcppt::make_shared_ptr<
			volume_texture
		>(
			src,
			filter,
			flags));*/
}
#endif

sge::renderer::caps const
sge::opengl::device::caps() const
{
	if(!caps_)
	{
		caps_.take(
			create_caps(
				context_
			)
		);
	}

	return *caps_;
}

sge::renderer::screen_size const
sge::opengl::device::screen_size() const
{
	return param.display_mode().size();
}

sge::window::instance_ptr const
sge::opengl::device::window() const
{
	return wnd;
}

GLenum
sge::opengl::device::clear_bit(
	renderer::state::bool_::trampoline_type const &s
) const
{
	return
		current_states.get(s)
		?
			convert::clear_bit(s)
		:
			0;
}

sge::opengl::fbo_target_ptr const
sge::opengl::device::create_target()
{
	return fcppt::make_shared_ptr<
		fbo_target
	>();
}

void
sge::opengl::device::reset_viewport(
	sge::window::dim_type const &wnd_sz
)
{
	opengl::viewport(
		renderer::viewport(
			viewport_pos(
				viewport_.pos(),
				wnd_sz,
				screen_size(),
				viewport_mode_
			),
			viewport_.size()
		),
		wnd_sz.h()
	);

	// use viewport_pos to calculate the position of
	// the backbuffer as well but starting with an offset of null
	default_target_->pos(
		viewport_pos(
			renderer::pixel_pos::null(),
			wnd_sz,
			screen_size(),
			viewport_mode_
		)
	);

	default_target_->dim(
		background_dim(
			viewport_mode_,
			wnd_sz,
			screen_size()
		)
	);
}

void
sge::opengl::device::reset_viewport_default()
{
	reset_viewport(
		wnd->size()
	);
}

void
sge::opengl::device::projection_internal()
{
	opengl::set_matrix_and_mode(
		context_,
		GL_PROJECTION,
		fbo_active
		? fbo_projection(
			projection_
		)
		: projection_
	);
}
