/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/config.h>
#ifdef SGE_WINDOWS_PLATFORM
#include "../wgl_current.hpp"
#include "../wgl_context.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/gdi_device.hpp>

sge::ogl::wgl_current::wgl_current(const gdi_device& dev, const wgl_context& ctx)
{
	if(wglMakeCurrent(dev.hdc(), ctx.hglrc()) == FALSE)
		throw exception(SGE_TEXT("wglMakeCurrent() failed!"));
}

sge::ogl::wgl_current::~wgl_current()
{
	wglMakeCurrent(0,0);
}

#endif
