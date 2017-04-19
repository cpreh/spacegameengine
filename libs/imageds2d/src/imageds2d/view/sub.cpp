/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/impl/view/instantiate_sub.hpp>
#include <sge/image/impl/view/sub_impl.hpp>
#include <sge/imageds2d/rect.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/traits/dimension.hpp>
#include <sge/imageds2d/view/const_object.hpp>
#include <sge/imageds2d/view/object.hpp>
#include <sge/imageds2d/view/sub.hpp>


sge::imageds2d::view::object
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

sge::imageds2d::view::const_object
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

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB(
	sge::imageds2d::tag
);
