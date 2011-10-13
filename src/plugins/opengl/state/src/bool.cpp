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


#include "../bool.hpp"
#include "../parameters.hpp"
#include "../convert/bool.hpp"
#include "../deferred/bundle.hpp"
#include "../deferred/object.hpp"
#include "../../check_state.hpp"
#include "../../common.hpp"
#include "../../enable_bool.hpp"
#include "../../multi_sample_context.hpp"
#include "../../point_sprite_context.hpp"
#include "../../convert/to_gl_bool.hpp"
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::state::bool_(
	state::parameters const &_parameters,
	renderer::state::bool_::type const &_state
)
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
			state::convert::bool_(
				_state
			),
			_state.value()
		);
		return;
	case rs::enable_point_sprites:
		if(
			!_parameters.point_sprite_context().is_supported()
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
			_parameters.point_sprite_context().point_sprite_flag(),
			_state.value()
		);

		opengl::enable_bool(
			_parameters.point_sprite_context().vertex_shader_size_flag(),
			_state.value()
		);

		return;
	case rs::enable_multi_sampling:
		if(
			!_parameters.multi_sample_context().is_supported()
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
			_parameters.multi_sample_context().flag(),
			_state.value()
		);

		return;
	case rs::write_to_depth_buffer:
		::glDepthMask(
			opengl::convert::to_gl_bool(
				_state.value()
			)
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glDepthMask failed"),
			sge::renderer::exception
		)
	case rs::write_alpha:
	case rs::write_blue:
	case rs::write_green:
	case rs::write_red:
		_parameters.deferred().add(
			deferred::bundle::color_write
		);
		return;
	}

	FCPPT_ASSERT_UNREACHABLE
}
