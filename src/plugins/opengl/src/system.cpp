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


#include "../system.hpp"
#include "../device.hpp"
#include <sge/renderer/caps.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::system::system()
: created(false)
{}

sge::renderer::device_ptr const
sge::ogl::system::create_renderer(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window_ptr const wnd)
{
	if(created)
		throw exception(
			SGE_TEXT("The opengl plugin may only be used once for creating a device."));
	renderer::device_ptr const r(
		new device(param, adapter, wnd));
	created = true; // FIXME: use a weak_ptr here!
	return r;
}

sge::renderer::caps_array const
sge::ogl::system::caps() const
{
	renderer::caps_array v;
	return v; // FIXME
}
