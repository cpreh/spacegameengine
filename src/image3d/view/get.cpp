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


#include <sge/image/color/any/object.hpp>
#include <sge/image/color/traits/any_object_fwd.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/traits/color_tag.hpp>
#include <sge/image3d/traits/const_view_fwd.hpp>
#include <sge/image3d/traits/dim_fwd.hpp>
#include <sge/image3d/traits/view_fwd.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/get.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/src/image/view/get_impl.hpp>
#include <sge/src/image/view/instantiate_get.hpp>


sge::image::color::any::object const
sge::image3d::view::get(
	sge::image3d::view::object const &_view,
	sge::image3d::dim const &_index
)
{
	return
		sge::image::view::get<
			sge::image3d::tag
		>(
			_view,
			_index
		);
}

sge::image::color::any::object const
sge::image3d::view::get(
	sge::image3d::view::const_object const &_view,
	sge::image3d::dim const &_index
)
{
	return
		sge::image::view::get<
			sge::image3d::tag
		>(
			_view,
			_index
		);
}

SGE_SRC_IMAGE_VIEW_INSTANTIATE_GET(
	sge::image3d::tag
);
