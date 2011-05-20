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


#include "../state_visitor.hpp"
#include "../split_states.hpp"
#include "../enable.hpp"
#include "../enable_bool.hpp"
#include "../disable.hpp"
#include "../check_state.hpp"
#include "../multi_sample_context.hpp"
#include "../point_sprite_context.hpp"
#include "../context/use.hpp"
#include "../convert/bool.hpp"
#include "../convert/cull_mode.hpp"
#include "../convert/fog_mode.hpp"
#include "../convert/draw_mode.hpp"
#include "../convert/depth_func.hpp"
#include "../convert/fog_float_state.hpp"
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/rgba32f.hpp>
#include <sge/renderer/buffer_has_depth.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/var.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/text.hpp>

sge::opengl::state_visitor::state_visitor(
	opengl::context::object &_context,
	split_states &_states,
	renderer::depth_stencil_buffer::type const _depth_stencil_buffer
)
:
	multi_sample_context_(
		context::use<
			multi_sample_context
		>(
			_context
		)
	),
	point_sprite_context_(
		context::use<
			point_sprite_context
		>(
			_context
		)
	),
	states_(_states),
	depth_stencil_buffer_(_depth_stencil_buffer)
{
}

sge::opengl::state_visitor::~state_visitor()
{
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::int_::type const _state
) const
{
	namespace rs = renderer::state::int_::available_states;

	switch(
		_state.state()
	)
	{
	case rs::stencil_buffer_clear_val:
		::glClearStencil(
			_state.value()
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glClearStencil failed"),
			sge::renderer::exception
		)
		return;
	case rs::stencil_ref:
		states_.update_stencil(
			depth_stencil_buffer_
		);
		return;
	}
	
	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid int_state!")
	);
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::uint::type const _state
) const
{
	namespace rs = renderer::state::uint::available_states;

	switch(
		_state.state()
	)
	{
	case rs::stencil_mask:
		states_.update_stencil(
			depth_stencil_buffer_
		);
		return;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid uint_state!")
	);
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::float_::type const &_state
) const
{
	namespace rs = renderer::state::float_::available_states;

	switch(
		_state.state()
	)
	{
	case rs::depth_buffer_clear_val:
		::glClearDepth(
			static_cast<
				GLdouble
			>(
				_state.value()
			)
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glClearDepth failed"),
			sge::renderer::exception
		)

		return;
	case rs::alpha_test_ref:
		states_.update_alpha_test();
		return;
	case rs::fog_start:
	case rs::fog_end:
	case rs::fog_density:
		::glFogf(
			convert::fog_float_state(
				_state
			),
			static_cast<
				GLfloat
			>(
				_state.value()
			)
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glFogf failed"),
			sge::renderer::exception
		)

		return;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid float_state!")
	);
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::bool_::type const _state
) const
{
	// don't complain about unsupported but disabled states in case we don't support them
	// because the default renderer settings will at least try to disable them

	namespace rs = renderer::state::bool_::available_states;

	switch(
		_state.state()
	)
	{
	case rs::clear_back_buffer:
	case rs::clear_depth_buffer:
	case rs::clear_stencil_buffer:
		return;
	case rs::enable_alpha_blending:
	case rs::enable_lighting:
	case rs::enable_scissor_test:
		opengl::enable_bool(
			convert::bool_(
				_state
			),
			_state.value()
		);
		return;
	case rs::enable_point_sprites:
		if(
			!point_sprite_context_.is_supported()
		)
		{
			if(
				!_state.value()
			)
				return;

			throw sge::renderer::unsupported(
				FCPPT_TEXT("GL_POINT_SPRITE"),
				FCPPT_TEXT("opengl-2.0"),
				FCPPT_TEXT("ARB_point_sprite")
			);
		}

		opengl::enable_bool(
			point_sprite_context_.point_sprite_flag(),
			_state.value()
		);

		opengl::enable_bool(
			point_sprite_context_.vertex_shader_size_flag(),
			_state.value()
		);

		return;
	case rs::enable_multi_sampling:
		if(
			!multi_sample_context_.is_supported()
		)
		{
			if(
				!_state.value()
			)
				return;

			throw sge::renderer::unsupported(
				FCPPT_TEXT("multi sampling"),
				FCPPT_TEXT("GL_VERSION_1_3"),
				FCPPT_TEXT("GL_ARB_multisample")
			);
		}

		opengl::enable_bool(
			multi_sample_context_.flag(),
			_state.value()
		);

		return;
	case rs::write_to_depth_buffer:
		::glDepthMask(
			_state.value()
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glDepthMask failed"),
			sge::renderer::exception
		)

		return;
	}
	
	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid bool_state!")
	);
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::color::type const &_state
) const
{
	namespace rs = renderer::state::color::available_states;

	image::color::rgba32f const fcolor(
		image::color::any::convert<
			image::color::rgba32f_format
		>(
			_state.value()
		)
	);

	switch(
		_state.state()
	)
	{
	case rs::back_buffer_clear_color:
		::glClearColor(
			fcolor.get<mizuiro::color::channel::red>(),
			fcolor.get<mizuiro::color::channel::green>(),
			fcolor.get<mizuiro::color::channel::blue>(),
			fcolor.get<mizuiro::color::channel::alpha>()
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glClearColor failed"),
			sge::renderer::exception
		)
		return;
	case rs::ambient_light_color:
		::glLightModelfv(
			GL_LIGHT_MODEL_AMBIENT,
			fcolor.data()
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glLightMOdelfv failed"),
			sge::renderer::exception
		)

		return;
	case rs::fog_color:
		::glFogfv(
			GL_FOG_COLOR,
			fcolor.data()
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glFogfv failed"),
			sge::renderer::exception
		)

		return;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid color_state!")
	);
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::cull_mode::type const _mode
) const
{
	if(
		_mode == renderer::state::cull_mode::off
	)
	{
		opengl::disable(
			GL_CULL_FACE
		);

		return;
	}

	opengl::enable(
		GL_CULL_FACE
	);

	::glCullFace(
		convert::cull_mode(
			_mode
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glCullFace failed"),
		sge::renderer::exception
	)
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::depth_func::type const _func
) const
{
	if(
		_func == renderer::state::depth_func::off
	)
	{
		opengl::disable(
			GL_DEPTH_TEST
		);

		return;
	}

	if(
		!sge::renderer::buffer_has_depth(
			depth_stencil_buffer_
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("You tried to use a depth_func besides depth_func::off.")
			FCPPT_TEXT(" This will only work if you request a depth buffer in renderer::parameters!")
		);

	opengl::enable(
		GL_DEPTH_TEST
	);

	::glDepthFunc(
		convert::depth_func(
			_func	
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDepthFunc failed"),
		sge::renderer::exception
	)
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::stencil_func::type
) const
{
	states_.update_stencil(
		depth_stencil_buffer_
	);
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::alpha_func::type
) const
{
	states_.update_alpha_test();
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::fog_mode::type const _mode
) const
{
	if(
		_mode == renderer::state::fog_mode::off
	)
	{
		opengl::disable(
			GL_FOG
		);

		return;
	}

	opengl::enable(
		GL_FOG
	);

	::glFogi(
		GL_FOG_MODE,
		convert::fog_mode(
			_mode
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glFogi failed"),
		sge::renderer::exception
	)
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::draw_mode::type const _mode
) const
{
	::glPolygonMode(
		GL_FRONT_AND_BACK,
		convert::draw_mode(
			_mode
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glPolygonMode failed"),
		sge::renderer::exception
	)
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::source_blend_func::type
) const
{
	states_.update_blend();
}

sge::opengl::state_visitor::result_type
sge::opengl::state_visitor::operator()(
	renderer::state::dest_blend_func::type
) const
{
	states_.update_blend();
}
