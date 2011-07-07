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


#ifndef SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_COPY_HPP_INCLUDED
#define SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_COPY_HPP_INCLUDED

#include "../../view/color_layout.hpp"
#include <mizuiro/image/algorithm/copy_different_channel_order.hpp>
#include <mizuiro/image/algorithm/copy_same_channel_order.hpp>
#include <fcppt/container/array_comparison.hpp>

namespace sge
{
namespace image
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
	Dest const &_dest
)
{
	if(
		view::color_layout(
			_source
		)
		==
		view::color_layout(
			_dest
		)
	)
		mizuiro::image::algorithm::copy_same_channel_order(
			_source,
			_dest
		);
	else
		mizuiro::image::algorithm::copy_different_channel_order(
			_source,
			_dest
		);
}

}
}
}
}
}

#endif
