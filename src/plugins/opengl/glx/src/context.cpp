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


#include "../context.hpp"
#include <sge/x11/display.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::glx::context::context(
	x11::display_ptr const dsp,
	XVisualInfo const &vi)
:
	dsp(dsp),
	c(
		glXCreateContext(
			dsp->get(),
			const_cast<XVisualInfo*>(&vi),
			NULL,
			True))
{
	if(c == 0)
		throw exception(
			SGE_TEXT("glXCreateContext() failed!"));
}

sge::ogl::glx::context::~context()
{
	glXDestroyContext(
		dsp->get(),
		get());
}

GLXContext &
sge::ogl::glx::context::get()
{
	return c;
}
