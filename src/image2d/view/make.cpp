/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/traits/color_tag.hpp>
#include <sge/image2d/traits/dim_fwd.hpp>
#include <sge/image2d/traits/pitch_fwd.hpp>
#include <sge/image2d/traits/view_elements.hpp>
#include <sge/image2d/traits/view_fwd.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/src/image/view/instantiate_make.hpp>
#include <sge/src/image/view/make_impl.hpp>


sge::image2d::view::object const
sge::image2d::view::make(
	sge::image::raw_pointer const _data,
	sge::image2d::dim const &_dim,
	sge::image::color::format const _format,
	sge::image2d::pitch const &_pitch
)
{
	return
		sge::image::view::make<
			sge::image2d::tag
		>(
			_data,
			_dim,
			_format,
			_pitch
		);
}

SGE_SRC_IMAGE_VIEW_INSTANTIATE_MAKE(
	sge::image2d::tag
);
