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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_COPY_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_ALGORITHM_CAC_COPY_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/src/image/algorithm/convert_may_overlap.hpp>
#include <sge/src/image/algorithm/convert_uninitialized.hpp>
#include <sge/src/image/color/dynamic/view/color_layout.hpp>
#include <mizuiro/image/algorithm/copy_different_channel_order.hpp>
#include <mizuiro/image/algorithm/copy_same_channel_order.hpp>
#include <mizuiro/image/algorithm/may_overlap.hpp>
#include <mizuiro/image/algorithm/uninitialized.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

template<
	typename Source,
	typename Dest
>
void
copy(
	Source const &_source,
	Dest const &_dest,
	sge::image::algorithm::may_overlap const _overlap,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	mizuiro::image::algorithm::may_overlap const mizuiro_overlap(
		sge::image::algorithm::convert_may_overlap(
			_overlap
		)
	);

	mizuiro::image::algorithm::uninitialized const mizuiro_uninitialized(
		sge::image::algorithm::convert_uninitialized(
			_uninitialized
		)
	);


	if(
		sge::image::color::dynamic::view::color_layout(
			_source
		)
		==
		sge::image::color::dynamic::view::color_layout(
			_dest
		)
	)
		mizuiro::image::algorithm::copy_same_channel_order(
			_source,
			_dest,
			mizuiro_overlap,
			mizuiro_uninitialized
		);
	else
		mizuiro::image::algorithm::copy_different_channel_order(
			_source,
			_dest,
			mizuiro_overlap,
			mizuiro_uninitialized
		);
}

}
}
}
}
}
}

#endif
