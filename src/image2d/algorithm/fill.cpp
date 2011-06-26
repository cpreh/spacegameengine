/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../../image/algorithm/fill_impl.hpp"
#include "../../image/algorithm/instantiate_fill.hpp"
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/tag.hpp>

void
sge::image2d::algorithm::fill(
	view::object const &_dest,
	image::color::any::object const &_col
)
{
	sge::image::algorithm::fill<
		sge::image2d::tag
	>(
		_dest,
		_col
	);
}

SGE_IMAGE_ALGORITHM_INSTANTIATE_FILL(
	sge::image2d::tag
)
