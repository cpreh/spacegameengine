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



#include "../viewport.hpp"
#include "../check_state.hpp"
#include "../common.hpp"
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/text.hpp>

void
sge::ogl::viewport(
	renderer::viewport const &v,
	renderer::screen_unit const h)
{
	glViewport(
		v.pos().x(),
		h - v.size().h() - v.pos().y(),
		v.size().w(),
		v.size().h()
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glViewport failed"),
		sge::renderer::exception
	)
}
