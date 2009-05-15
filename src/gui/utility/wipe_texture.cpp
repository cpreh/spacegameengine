/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "wipe_texture.hpp"
#include "wipe_image_view.hpp"
#include <sge/renderer/texture.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/math/rect/basic_impl.hpp>

void sge::gui::utility::wipe_texture(
	renderer::texture_ptr const t)
{
	renderer::scoped_texture_lock const lock_(
		t,
		renderer::lock_rect(
			renderer::lock_rect::point_type::null(),
			t->dim()
		),
		renderer::lock_flags::readwrite);
	
	wipe_image_view(
		lock_.value());
}
