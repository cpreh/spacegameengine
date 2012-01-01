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


#ifndef SGE_OPENGL_X11_RESOLUTION_XF86_VMODE_HPP_INCLUDED
#define SGE_OPENGL_X11_RESOLUTION_XF86_VMODE_HPP_INCLUDED

#include <sge/opengl/x11/resolution/instance.hpp>
#include <sge/opengl/xf86vmode/modes.hpp>
#include <sge/opengl/xf86vmode/resolution_ptr.hpp>
#include <sge/renderer/display_mode_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/screen.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace x11
{
namespace resolution
{

class xf86_vmode
:
	public instance
{
	FCPPT_NONCOPYABLE(
		xf86_vmode
	);
public:
	xf86_vmode(
		renderer::display_mode const &,
		awl::backends::x11::display &,
		awl::backends::x11::screen
	);

	~xf86_vmode();
private:
	xf86vmode::modes const modes_;

	xf86vmode::resolution_ptr const resolution_;
};

}
}
}
}

#endif
