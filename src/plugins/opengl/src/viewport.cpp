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


#include "../viewport.hpp"
#include "../check_state.hpp"
#include "../common.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::viewport(
	renderer::viewport const &_viewport,
	renderer::screen_unit const _height
)
{
	::glViewport(
		static_cast<
			GLint
		>(
			_viewport.pos().x()
		),
		static_cast<
			GLint
		>(
			static_cast<
				renderer::pixel_unit
			>(
				_height
			)
			- _viewport.size().h()
			- _viewport.pos().y()
		),
		static_cast<
			GLsizei
		>(
			_viewport.size().w()
		),
		static_cast<
			GLsizei
		>(
			_viewport.size().h()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glViewport failed"),
		sge::renderer::exception
	)
}
