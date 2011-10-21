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


#include "../color_write.hpp"
#include "../../../check_state.hpp"
#include "../../../common.hpp"
#include "../../../convert/to_gl_bool.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::state::deferred::color_write(
	deferred::parameters const &,
	sge::renderer::state::list const &_list
)
{
	::glColorMask(
		opengl::convert::to_gl_bool(
			_list.get(
				sge::renderer::state::bool_::write_red
			)
		),
		opengl::convert::to_gl_bool(
			_list.get(
				sge::renderer::state::bool_::write_blue
			)
		),
		opengl::convert::to_gl_bool(
			_list.get(
				sge::renderer::state::bool_::write_green
			)
		),
		opengl::convert::to_gl_bool(
			_list.get(
				sge::renderer::state::bool_::write_alpha
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glColorMask failed"),
		sge::renderer::exception
	)
}
