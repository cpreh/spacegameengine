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


#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/color/impl/traits/format_map.hpp>
#include <sge/image/impl/view/instantiate_make.hpp>
#include <sge/image/impl/view/make_impl.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/pitch.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/traits/color_tag.hpp>
#include <sge/image3d/traits/dimension.hpp>
#include <sge/image3d/view/make.hpp>
#include <sge/image3d/view/object.hpp>


sge::image3d::view::object
sge::image3d::view::make(
	sge::image::raw_pointer const _data,
	sge::image3d::dim const &_dim,
	sge::image::color::format const _format,
	sge::image3d::pitch const &_pitch
)
{
	return
		sge::image::view::make<
			sge::image3d::tag
		>(
			_data,
			_dim,
			_format,
			_pitch
		);
}

SGE_IMAGE_IMPL_VIEW_INSTANTIATE_MAKE(
	sge::image3d::tag
);
