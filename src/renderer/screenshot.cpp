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


#include <sge/renderer/screenshot.hpp>
#include <sge/vector.hpp>
#include <vector>

void sge::renderer::screenshot(
	const device_ptr rend,
	const sge::image::loader_ptr il,
	const path& file)
{
	const target_ptr target = rend->get_target();
	std::vector<color> buf(target->size());
	// FIXME: do this with boost::gil too!
	//target->copy_data(sge::data(buf));
	const sge::image::image_ptr shot = il->create_image(sge::data(buf), target->dim());
	shot->save(file);
}
