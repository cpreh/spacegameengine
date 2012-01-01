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


#include <sge/image2d/save_from_view.hpp>
#include <sge/renderer/const_scoped_color_surface_lock.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/screenshot.hpp>
#include <fcppt/filesystem/path.hpp>


void
sge::renderer::screenshot(
	renderer::device const &_renderer,
	image2d::system &_system,
	fcppt::filesystem::path const &_path
)
{
	renderer::const_scoped_color_surface_lock const lock(
		_renderer.onscreen_target().surface()
	);

	sge::image2d::save_from_view(
		_system,
		lock.value(),
		_path
	);
}
