/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../device.hpp"
#include "../apply_states.hpp"
#include "../check_state.hpp"
#include "../common.hpp"
#include "../create_caps.hpp"
#include "../create_device_state.hpp"
#include "../cube_texture.hpp"
#include "../default_target.hpp"
#include "../depth_stencil_texture.hpp"
#include "../device_state.hpp"
#include "../enable_bool.hpp"
#include "../index_buffer.hpp"
#include "../initial_states.hpp"
#include "../set_clip_plane.hpp"
#include "../set_light.hpp"
#include "../set_material.hpp"
#include "../set_matrix_and_mode.hpp"
#include "../set_scissor_area.hpp"
#include "../set_texture.hpp"
#include "../set_texture_stage.hpp"
#include "../set_texture_stage_scale.hpp"
#include "../texture.hpp"
#include "../vertex_buffer.hpp"
#include "../volume_texture.hpp"
#include "../volume_texture_context.hpp"
#include "../context/use.hpp"
#include "../convert/clear_bit.hpp"
#include "../convert/clip_plane_index.hpp"
#include "../convert/indexed_primitive.hpp"
#include "../convert/light_index.hpp"
#include "../convert/matrix_mode.hpp"
#include "../convert/nonindexed_primitive.hpp"
#include "../fbo/target.hpp"
#include "../glew/initialize.hpp"
#include "../glsl/set_program.hpp"
#include "../glsl/create_program.hpp"
#include "../glsl/create_vertex_shader.hpp"
#include "../glsl/create_pixel_shader.hpp"
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

sge::opengl::device::device(
	renderer::parameters const &_parameters,
	renderer::adapter_type const _adapter,
	window::instance_ptr const _window
)
:
	parameters_(_parameters),
	window_(_window),
	current_states_(
		opengl::initial_states()
	),
	state_(
		opengl::create_device_state(
			_parameters,
			_adapter,
			_window
		)
	),
	default_target_(
		fcppt::make_shared_ptr<
			opengl::default_target
		>(
			_window,
			_parameters.display_mode().bit_depth()
		)
	),
	target_(
		default_target_
	),
	caps_(),
	state_levels_(),
	context_()
{
	glew::initialize();

	state(
		sge::renderer::state::default_()
	);

	target_->bind();
}

sge::opengl::device::~device()
{
}

void
sge::opengl::device::begin_rendering()
{
	::glClear(
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
	if(
		!fbo_active()
	)
		state_->swap_buffers();
}

void
sge::opengl::device::render(
	renderer::const_index_buffer_ptr const _ib,
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::indexed_primitive_type::type const _ptype,
	renderer::primitive_count const _pcount,
	renderer::first_index const _first_index
)
{
	index_buffer_base const & gl_ib(
		dynamic_cast<
			index_buffer_base const &
		>(
			*_ib
		)
	);

	gl_ib.bind_me();

	glDrawElements(
		convert::indexed_primitive(
			_ptype
		),
		static_cast<
			GLsizei
		>(
			renderer::indices_per_primitive(
				_ptype
			) * _pcount
		),
		gl_ib.gl_format(),
		gl_ib.buffer_offset(
			_first_index
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
	renderer::state::list const &_states
)
{
	opengl::apply_states(
		context_,
		current_states_,
		_states,
		parameters_
	);
}

void
sge::opengl::device::push_state(
	renderer::state::list const &_states
)
{
	state_levels_.push(
		current_states_
	);

	state(
		_states
	);
}

void
sge::opengl::device::pop_state()
{
	state(
		state_levels_.top()
	);

	state_levels_.pop();
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
	renderer::light_index const _index,
	bool const _enable
)
{
	opengl::enable_bool(
		convert::light_index(
			_index
		),
		_enable
	);
}

void
sge::opengl::device::light(
	renderer::light_index const _index,
	renderer::light const &_light
)
{
	opengl::set_light(
		_index,
		_light
	);
}

void
sge::opengl::device::enable_clip_plane(
	renderer::clip_plane_index const _index,
	bool const _enable
)
{
	opengl::enable_bool(
		convert::clip_plane_index(
			_index
		),
		_enable
	);
}

void
sge::opengl::device::clip_plane(
	renderer::clip_plane_index const _index,
	renderer::clip_plane const &_clip_plane
)
{
	opengl::set_clip_plane(
		_index,
		_clip_plane
	);
}

void
sge::opengl::device::scissor_area(
	renderer::scissor_area const &_area
)
{
	opengl::set_scissor_area(
		_area
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
	renderer::const_texture_base_ptr const _texture,
	renderer::stage_type const _stage
)
{
	opengl::set_texture(
		context_,
		_texture,
		_stage
	);
}

void
sge::opengl::device::transform(
	renderer::matrix_mode::type const _mode,
	renderer::matrix4 const &_matrix
)
{
	opengl::set_matrix_and_mode(
		context_,
		convert::matrix_mode(
			_mode
		),
		_matrix
	);
}

void
sge::opengl::device::target(
	renderer::target_ptr const _target
)
{
	if(
		_target == target_
	)
		return;
	
	target_->unbind();

	target_ =
		_target
		?
			fcppt::dynamic_pointer_cast<
				opengl::target
			>(
				_target
			)
		:
			opengl::target_ptr(
				default_target_
			);
		
	target_->bind();

	target_->activate_viewport();
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
	renderer::glsl::const_program_ptr const prog
)
{
	glsl::set_program(
		context_,
		prog
	);
}

sge::renderer::target_ptr const
sge::opengl::device::target() const
{
	return target_;
}

sge::renderer::target_ptr const
sge::opengl::device::create_target(
	renderer::texture_ptr const _texture,
	renderer::depth_stencil_texture_ptr const _depth_stencil_texture
)
{
	FCPPT_ASSERT(
		_texture || _depth_stencil_texture
	);

	return
		fcppt::make_shared_ptr<
			fbo::target
		>(
			std::tr1::ref(
				context_
			),
			parameters_,
			fcppt::dynamic_pointer_cast<
				opengl::texture
			>(
				_texture
			),
			fcppt::dynamic_pointer_cast<
				opengl::depth_stencil_texture
			>(
				_depth_stencil_texture
			)
		);
}

sge::renderer::texture_ptr const
sge::opengl::device::create_texture(
	renderer::texture::dim_type const &_dim,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags
)
{
	return
		renderer::texture_ptr(
			fcppt::make_shared_ptr<
				opengl::texture
			>(
				std::tr1::ref(
					context_
				),
				_dim,
				_format,
				_filter,
				_flags,
				opengl::texture::optional_type()
			)
		);
}

sge::renderer::depth_stencil_texture_ptr const
sge::opengl::device::create_depth_stencil_texture(
	renderer::dim2 const &_dim,
	renderer::depth_stencil_format::type const _format
)
{
	return
		renderer::depth_stencil_texture_ptr(
			fcppt::make_shared_ptr<
				opengl::depth_stencil_texture
			>(
				std::tr1::ref(
					context_
				),
				_dim,
				_format
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

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid index::format!")
	);
}

sge::renderer::volume_texture_ptr const
sge::opengl::device::create_volume_texture(
	renderer::dim3 const &_dim,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter,
	renderer::resource_flags_field const &_flags
)
{
	if(
		!context::use<
			opengl::volume_texture_context
		>(
			context_
		).have_volume_texture()
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("volume texture"),
			FCPPT_TEXT("1.2"),
			FCPPT_TEXT("")
		);

	return
		renderer::volume_texture_ptr(
			fcppt::make_shared_ptr<
				opengl::volume_texture
			>(
				std::tr1::ref(
					context_
				),
				_dim,
				_format,
				_filter,
				_flags
			)
		);
}

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
	return parameters_.display_mode().size();
}

sge::window::instance_ptr const
sge::opengl::device::window() const
{
	return window_;
}

GLenum
sge::opengl::device::clear_bit(
	renderer::state::bool_::trampoline_type const &_state
) const
{
	return
		current_states_.get(
			_state
		)
		?
			convert::clear_bit(
				_state
			)
		:
			0;
}

bool
sge::opengl::device::fbo_active() const
{
	return target_ != default_target_;
}
