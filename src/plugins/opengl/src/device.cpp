/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../device_state.hpp"
#include "../draw_arrays.hpp"
#include "../draw_elements.hpp"
#include "../enable_bool.hpp"
#include "../get_matrix.hpp"
#include "../get_scissor_area.hpp"
#include "../index_buffer.hpp"
#include "../initial_states.hpp"
#include "../onscreen_target.hpp"
#include "../set_clip_plane.hpp"
#include "../set_light.hpp"
#include "../set_material.hpp"
#include "../set_matrix_and_mode.hpp"
#include "../set_scissor_area.hpp"
#include "../vertex_buffer.hpp"
#include "../context/use.hpp"
#include "../convert/clear_bit.hpp"
#include "../convert/clip_plane_index.hpp"
#include "../convert/light_index.hpp"
#include "../convert/matrix_mode.hpp"
#include "../fbo/create_depth_stencil_surface.hpp"
#include "../fbo/target.hpp"
#include "../glew/initialize.hpp"
#include "../glsl/set_program.hpp"
#include "../glsl/create_program.hpp"
#include "../glsl/create_vertex_shader.hpp"
#include "../glsl/create_pixel_shader.hpp"
#include "../texture/activate.hpp"
#include "../texture/cube.hpp"
#include "../texture/depth_stencil.hpp"
#include "../texture/optional_type.hpp"
#include "../texture/planar.hpp"
#include "../texture/set_stage_funcs.hpp"
#include "../texture/set_stage_scale.hpp"
#include "../texture/volume.hpp"
#include "../texture/volume_context.hpp"
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/default.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
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
	onscreen_target_(
		fcppt::make_shared_ptr<
			opengl::onscreen_target
		>(
			_window,
			_parameters.display_mode().bit_depth()
		)
	),
	fbo_target_(),
	target_(
		onscreen_target_
	),
	caps_(),
	state_levels_(),
	context_()
{
	glew::initialize();

	this->state(
		sge::renderer::state::default_()
	);

	target_->use();
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
	opengl::draw_elements(
		context_,
		_ib,
		_first_vertex,
		_num_vertices,
		_ptype,
		_pcount,
		_first_index
	);
}

void
sge::opengl::device::render(
	renderer::first_vertex const _first_vertex,
	renderer::vertex_count const _num_vertices,
	renderer::nonindexed_primitive_type::type const _ptype
)
{
	opengl::draw_arrays(
		_first_vertex,
		_num_vertices,
		_ptype
	);
}

void
sge::opengl::device::set_vertex_buffer(
	renderer::const_vertex_buffer_ptr const _vb
)
{
	dynamic_cast<
		opengl::vertex_buffer const &
	>(
		*_vb
	).set_format();
}

void
sge::opengl::device::unset_vertex_buffer(
	renderer::const_vertex_buffer_ptr const _vb
)
{
	dynamic_cast<
		opengl::vertex_buffer const &
	>(
		*_vb
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
	renderer::material const &_mat
)
{
	opengl::set_material(
		_mat
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
sge::opengl::device::sampler_stage_op(
	renderer::stage_type const _stage,
	renderer::sampler_stage_op::type const _op,
	renderer::sampler_stage_op_value::type const _value
)
{
	opengl::texture::set_stage_funcs(
		context_,
		_stage,
		_op,
		_value
	);

	opengl::texture::set_stage_scale(
		_value
	);
}

void
sge::opengl::device::sampler_stage_arg(
	renderer::stage_type const _stage,
	renderer::sampler_stage_arg::type const _arg,
	renderer::sampler_stage_arg_value::type const _value
)
{
	opengl::texture::set_stage_funcs(
		context_,
		_stage,
		_arg,
		_value
	);
}

void
sge::opengl::device::texture(
	renderer::texture::const_base_ptr const _texture,
	renderer::stage_type const _stage
)
{
	opengl::texture::activate(
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
		_target == fbo_target_
	)
		return;
	
	fbo_target_ =
		fcppt::dynamic_pointer_cast<
			opengl::fbo::target
		>(
			_target
		);

	target_->unbind();

	target_ =
		_target
		?
			opengl::target_base_ptr(
				fbo_target_
			)
		:
			opengl::target_base_ptr(
				onscreen_target_
			);

	target_->use();
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
	renderer::glsl::const_program_ptr const _program
)
{
	glsl::set_program(
		context_,
		_program
	);
}

sge::renderer::target_ptr const
sge::opengl::device::target() const
{
	return fbo_target_;
}

sge::renderer::target_ptr const
sge::opengl::device::create_target()
{
	return
		fcppt::make_shared_ptr<
			fbo::target
		>(
			std::tr1::ref(
				context_
			)
		);
}

sge::renderer::texture::planar_ptr const
sge::opengl::device::create_planar_texture(
	renderer::texture::planar_parameters const &_params
)
{
	return
		renderer::texture::planar_ptr(
			fcppt::make_shared_ptr<
				opengl::texture::planar
			>(
				std::tr1::ref(
					context_
				),
				_params,
				opengl::texture::optional_type()
			)
		);
}

sge::renderer::texture::depth_stencil_ptr const
sge::opengl::device::create_depth_stencil_texture(
	renderer::dim2 const &_dim,
	renderer::depth_stencil_format::type const _format
)
{
	return
		renderer::texture::depth_stencil_ptr(
			fcppt::make_shared_ptr<
				opengl::texture::depth_stencil
			>(
				std::tr1::ref(
					context_
				),
				_dim,
				_format
			)
		);
}

sge::renderer::depth_stencil_surface_ptr const
sge::opengl::device::create_depth_stencil_surface(
	renderer::dim2 const &_dim,
	renderer::depth_stencil_format::type const _type
)
{
	return
		renderer::depth_stencil_surface_ptr(
			opengl::fbo::create_depth_stencil_surface(
				std::tr1::ref(
					context_
				),
				_dim,
				_type
			)
		);
}

sge::renderer::texture::volume_ptr const
sge::opengl::device::create_volume_texture(
	renderer::texture::volume_parameters const &_param
)
{
	if(
		!context::use<
			opengl::texture::volume_context
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
		renderer::texture::volume_ptr(
			fcppt::make_shared_ptr<
				opengl::texture::volume
			>(
				std::tr1::ref(
					context_
				),
				_param
			)
		);
}

sge::renderer::texture::cube_ptr const
sge::opengl::device::create_cube_texture(
	renderer::texture::cube_parameters const &_param
)
{
	return
		renderer::texture::cube_ptr(
			fcppt::make_shared_ptr<
				opengl::texture::cube
			>(
				std::tr1::ref(
					context_
				),
				_param
			)
		);
}

sge::renderer::vertex_buffer_ptr const
sge::opengl::device::create_vertex_buffer(
	renderer::vf::dynamic::format const &_format,
	renderer::size_type const _size,
	renderer::resource_flags_field const &_flags
)
{
	return
		renderer::vertex_buffer_ptr(
			fcppt::make_shared_ptr<
				opengl::vertex_buffer
			>(
				std::tr1::ref(
					context_
				),
				_format,
				_size,
				_flags
			)
		);
}

sge::renderer::index_buffer_ptr const
sge::opengl::device::create_index_buffer(
	renderer::index::dynamic::format::type const _format,
	renderer::size_type const _size,
	renderer::resource_flags_field const &_flags
)
{
	return
		renderer::index_buffer_ptr(
			fcppt::make_shared_ptr<
				opengl::index_buffer
			>(
				std::tr1::ref(
					context_
				),
				_format,
				_size,
				_flags
			)
		);
}

sge::renderer::onscreen_target_ptr const
sge::opengl::device::onscreen_target() const
{
	return onscreen_target_;
}

sge::renderer::scissor_area const
sge::opengl::device::scissor_area() const
{
	return opengl::get_scissor_area();	
}
	
sge::renderer::matrix4 const
sge::opengl::device::transform(
	renderer::matrix_mode::type const _mode
)
{
	return
		opengl::get_matrix(
			_mode
		);
}

sge::renderer::caps const
sge::opengl::device::caps() const
{
	if(!caps_)
	{
		caps_.take(
			opengl::create_caps(
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
	return fbo_target_;
}
