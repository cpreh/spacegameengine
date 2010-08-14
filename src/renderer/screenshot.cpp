/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/screenshot.hpp>
#include <sge/renderer/const_scoped_target_lock.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/file.hpp>
#include <sge/image/multi_loader.hpp>
#include <sge/image/loader.hpp>
#include <fcppt/variant/object_impl.hpp>

void
sge::renderer::screenshot(
	const_device_ptr const rend,
	image::multi_loader const &il,
	fcppt::filesystem::path const &file
)
{
	// FIXME
	il.loaders().at(0)->create(
		const_scoped_target_lock(
			rend->target()
		).value()
	)->save(file);
}
