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



#include "../enable.hpp"
#include "../sentry.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/text.hpp>
#include <sge/format.hpp>

void sge::ogl::enable(
	GLenum const what,
	bool const enable_)
{
	if(enable_)
		enable(what);
	else
		disable(what);
}

void sge::ogl::enable(
	GLenum const what)
{
	SGE_OPENGL_SENTRY(
		sge::str(
			sge::format(
				SGE_TEXT("glEnable %1% failed")
			)
			% what
		),
		sge::renderer::exception
	)

	glEnable(what);
}

void sge::ogl::disable(
	GLenum const what)
{
	SGE_OPENGL_SENTRY(
		sge::str(
			sge::format(
				SGE_TEXT("glDisable %1% failed")
			)
			% what
		),
		sge::renderer::exception
	)
	
	glDisable(what);
}
