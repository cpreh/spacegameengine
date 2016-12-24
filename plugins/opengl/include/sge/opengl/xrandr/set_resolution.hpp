/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_XRANDR_SET_RESOLUTION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SET_RESOLUTION_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/optional_refresh_rate_fwd.hpp>
#include <sge/opengl/xrandr/rotation.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

void
set_resolution(
	awl::backends::x11::window::object &,
	sge::opengl::xrandr::configuration const &,
	sge::opengl::xrandr::mode_index,
	sge::opengl::xrandr::rotation,
	sge::opengl::xrandr::optional_refresh_rate const &
);

}
}
}

#endif
