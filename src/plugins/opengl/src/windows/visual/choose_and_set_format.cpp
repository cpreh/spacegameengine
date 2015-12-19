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


#include <sge/opengl/wgl/visual/choose_format.hpp>
#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/windows/visual/choose_and_set_format.hpp>
#include <sge/opengl/windows/visual/choose_format.hpp>
#include <sge/opengl/windows/visual/make_format.hpp>
#include <sge/opengl/windows/visual/set_format.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <awl/backends/windows/windows.hpp>


void
sge::opengl::windows::visual::choose_and_set_format(
	sge::opengl::wgl::visual::config const &_config,
	HWND const _hwnd,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	sge::opengl::windows::gdi_device const device(
		_hwnd,
		sge::opengl::windows::gdi_device::get_tag()
	);

	bool const needs_wgl(
		_pixel_format.multi_samples().has_value()
		||
		_pixel_format.srgb()
		==
		sge::renderer::pixel_format::srgb::yes
	);

	PIXELFORMATDESCRIPTOR const format_desc(
		sge::opengl::windows::visual::make_format(
			_pixel_format.color(),
			_pixel_format.depth_stencil()
		)
	);

	sge::opengl::windows::visual::set_format(
		device,
		needs_wgl
		?
			sge::opengl::wgl::visual::choose_format(
				device,
				_config,
				_pixel_format
			)
		:
			sge::opengl::windows::visual::choose_format(
				device,
				format_desc
			)
		,
		format_desc
	);
}
