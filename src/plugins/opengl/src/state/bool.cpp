/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>
#include <sge/opengl/state/bool.hpp>
#include <sge/opengl/state/parameters.hpp>
#include <sge/opengl/state/point_sprite.hpp>
#include <sge/opengl/state/convert/bool.hpp>
#include <sge/opengl/state/deferred/bundle.hpp>
#include <sge/opengl/state/deferred/object.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/bool/available_states.hpp>
#include <sge/renderer/state/bool/type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


void
sge::opengl::state::bool_(
	sge::opengl::state::parameters const &_parameters,
	sge::renderer::state::bool_::type const &_state
)
{
	// don't complain about unsupported but disabled states in case we don't support them
	// because the default renderer settings will at least try to disable them

	namespace rs = sge::renderer::state::bool_::available_states;

	switch(
		_state.state()
	)
	{
	case rs::enable_alpha_blending:
	case rs::enable_lighting:
	case rs::enable_scissor_test:
		sge::opengl::enable_bool(
			sge::opengl::state::convert::bool_(
				_state.state()
			),
			_state.value()
		);
		return;
	case rs::enable_point_sprites:
		sge::opengl::state::point_sprite(
			_parameters.system_context(),
			_state.value()
		);
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
		return;
	case rs::local_viewer:
		{
			GLint const value(
				_state.value()
				?
					1
				:
					0
			);

			::glLightModeliv(
				GL_LIGHT_MODEL_LOCAL_VIEWER,
				&value
			);

			SGE_OPENGL_CHECK_STATE(
				FCPPT_TEXT("glLightModeliv failed"),
				sge::renderer::exception
			)
		}
		return;
	case rs::write_to_depth_buffer:
		::glDepthMask(
			sge::opengl::convert::to_gl_bool(
				_state.value()
			)
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glDepthMask failed"),
			sge::renderer::exception
		)
		return;
	case rs::write_alpha:
	case rs::write_blue:
	case rs::write_green:
	case rs::write_red:
		_parameters.deferred().add(
			sge::opengl::state::deferred::bundle::color_write
		);
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
