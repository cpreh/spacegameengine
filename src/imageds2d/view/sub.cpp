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


#include <sge/imageds2d/rect.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/traits/box_fwd.hpp>
#include <sge/imageds2d/traits/const_view_fwd.hpp>
#include <sge/imageds2d/traits/view_fwd.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/object.hpp>
#include <sge/imageds2d/view/sub.hpp>
#include <sge/src/image/view/instantiate_sub.hpp>
#include <sge/src/image/view/sub_impl.hpp>


sge::imageds2d::view::object const
sge::imageds2d::view::sub(
	sge::imageds2d::view::object const &_src,
	sge::imageds2d::rect const &_rect
)
{
	return
		sge::image::view::sub<
			sge::imageds2d::tag
		>(
			_src,
			_rect
		);
}

sge::imageds2d::view::const_object const
sge::imageds2d::view::sub(
	sge::imageds2d::view::const_object const &_src,
	sge::imageds2d::rect const &_rect
)
{
	return
		sge::image::view::sub<
			sge::imageds2d::tag
		>(
			_src,
			_rect
		);
}

SGE_SRC_IMAGE_VIEW_INSTANTIATE_SUB(
	sge::imageds2d::tag
);
