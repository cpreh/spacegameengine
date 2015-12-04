/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/wgl/context.hpp>
#include <sge/opengl/wgl/current.hpp>
#include <sge/opengl/wgl/make_current.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::opengl::wgl::context::context(
	awl::backends::windows::window::object &_window
)
:
	sge::opengl::backend::context(),
	gdi_device_(
		_window.hwnd(),
		sge::opengl::windows::gdi_device::get_tag()
	),
	context_(
		gdi_device_
	)
{
}

sge::opengl::wgl::context::~context()
{
}

sge::opengl::backend::current_unique_ptr
sge::opengl::wgl::context::activate()
{
	sge::opengl::wgl::make_current(
		gdi_device_.hdc(),
		context_.get()
	);

	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::current
		>(
			fcppt::make_unique_ptr<
				sge::opengl::wgl::current
			>(
				gdi_device_
			)
		);
}

void
sge::opengl::wgl::context::deactivate(
	sge::opengl::backend::current_unique_ptr &&
)
{
	sge::opengl::wgl::make_current(
		nullptr,
		nullptr
	);
}
