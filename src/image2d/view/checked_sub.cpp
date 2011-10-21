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


#include "../../image/view/checked_sub_impl.hpp"
#include "../../image/view/instantiate_checked_sub.hpp"
#include <sge/image2d/tag.hpp>
#include <sge/image2d/view/checked_sub.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>


sge::image2d::view::object const
sge::image2d::view::checked_sub(
	view::object const &_view,
	image2d::rect const &_rect
)
{
	return
		sge::image::view::checked_sub<
			sge::image2d::tag
		>(
			_view,
			_rect
		);
}

sge::image2d::view::const_object const
sge::image2d::view::checked_sub(
	view::const_object const &_view,
	image2d::rect const &_rect
)
{
	return
		sge::image::view::checked_sub<
			sge::image2d::tag
		>(
			_view,
			_rect
		);
}

SGE_IMAGE_VIEW_INSTANTIATE_CHECKED_SUB(
	sge::image2d::tag
)
