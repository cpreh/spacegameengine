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


#include <sge/image2d/tag.hpp>
#include <sge/renderer/color_buffer/const_scoped_surface_lock.hpp>
#include <sge/renderer/color_buffer/readable_surface.hpp>
#include <sge/src/renderer/buffer/instantiate_const_scoped_lock.hpp>


SGE_RENDERER_BUFFER_INSTANTIATE_CONST_SCOPED_LOCK(
	sge::image2d::tag
);
