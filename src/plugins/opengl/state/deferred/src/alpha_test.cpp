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


#include "../alpha_test.hpp"
#include "../../convert/alpha_func.hpp"
#include "../../../check_state.hpp"
#include "../../../common.hpp"
#include "../../../disable.hpp"
#include "../../../enable.hpp"
#include <sge/renderer/state/alpha_func.hpp>
#include <sge/renderer/state/float.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::state::deferred::alpha_test(
	deferred::parameters const &,
	sge::renderer::state::list const &_list
)
{
	renderer::state::alpha_func::type const func(
		_list.get<
			renderer::state::alpha_func::type
		>()
	);

	if(
		func == renderer::state::alpha_func::off
	)
	{
		opengl::disable(
			GL_ALPHA_TEST
		);

		return;
	}

	opengl::enable(
		GL_ALPHA_TEST
	);

	::glAlphaFunc(
		state::convert::alpha_func(
			func
		),
		static_cast<
			GLfloat
		>(
			_list.get(
				renderer::state::float_::alpha_test_ref
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glAlphaFunc failed"),
		sge::renderer::exception
	)
}
