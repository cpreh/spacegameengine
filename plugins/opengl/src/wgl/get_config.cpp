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


#include <sge/opengl/wgl/config.hpp>
#include <sge/opengl/wgl/context_holder.hpp>
#include <sge/opengl/wgl/extension_set.hpp>
#include <sge/opengl/wgl/get_config.hpp>
#include <sge/opengl/wgl/get_extensions.hpp>
#include <sge/opengl/wgl/scoped_current.hpp>
#include <sge/opengl/wgl/visual/config.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/system/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <awl/window/object.hpp>
#include <awl/window/object_unique_ptr.hpp>
#include <awl/window/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_cross_exn.hpp>


sge::opengl::wgl::config
sge::opengl::wgl::get_config(
	awl::system::object &_awl_system
)
{
	awl::visual::object_unique_ptr const visual(
		_awl_system.default_visual()
	);

	awl::window::object_unique_ptr const window(
		_awl_system.create_window(
			awl::window::parameters(
				*visual
			)
			.class_name(
				FCPPT_TEXT("sgeopengl_dummy_window")
			)
		)
	);

	sge::opengl::windows::gdi_device const gdi_device(
		fcppt::cast::dynamic_cross_exn<
			awl::backends::windows::window::object &
		>(
			*window
		).hwnd(),
		sge::opengl::windows::gdi_device::get_tag()
	);

	sge::opengl::wgl::context_holder const context(
		gdi_device
	);

	sge::opengl::wgl::scoped_current const current(
		context,
		gdi_device
	);

	sge::opengl::wgl::extension_set const extensions(
		sge::opengl::wgl::get_extensions(
			current
		)
	);

	return
		sge::opengl::wgl::config(
			sge::opengl::wgl::visual::config(
				extensions,
				current
			)
		);
}
