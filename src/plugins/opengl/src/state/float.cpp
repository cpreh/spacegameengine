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


#include <sge/opengl/state/float.hpp>
#include <sge/opengl/state/parameters.hpp>
#include <sge/opengl/state/convert/fog_float.hpp>
#include <sge/opengl/state/deferred/bundle.hpp>
#include <sge/opengl/state/deferred/object.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/var.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


void
sge::opengl::state::float_(
	state::parameters const &_parameters,
	renderer::state::float_::type const &_state
)
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
		_parameters.deferred().add(
			deferred::bundle::alpha_test
		);
		return;
	case rs::fog_start:
	case rs::fog_end:
	case rs::fog_density:
		::glFogf(
			state::convert::fog_float(
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

	FCPPT_ASSERT_UNREACHABLE;
}
