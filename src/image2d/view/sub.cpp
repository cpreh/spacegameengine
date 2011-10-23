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


#include <sge/image2d/tag.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/src/image/view/sub_impl.hpp>
#include <sge/src/image/view/instantiate_sub.hpp>


sge::image2d::view::object const
sge::image2d::view::sub(
	view::object const &_src,
	image2d::rect const &_rect
)
{
	return
		sge::image::view::sub<
			sge::image2d::tag
		>(
			_src,
			_rect
		);
}

sge::image2d::view::const_object const
sge::image2d::view::sub(
	view::const_object const &_src,
	image2d::rect const &_rect
)
{
	return
		sge::image::view::sub<
			sge::image2d::tag
		>(
			_src,
			_rect
		);
}

SGE_SRC_IMAGE_VIEW_INSTANTIATE_SUB(
	sge::image2d::tag
)
