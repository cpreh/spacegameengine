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


#ifndef SGE_IMAGE_VIEW_MIZUIRO_TYPE_HPP_INCLUDED
#define SGE_IMAGE_VIEW_MIZUIRO_TYPE_HPP_INCLUDED

#include <mizuiro/image/view_impl.hpp>
#include <mizuiro/image/raw_view.hpp>
#include <mizuiro/image/interleaved.hpp>
#include <mizuiro/image/dimension_impl.hpp>
#include <mizuiro/image/format.hpp>
#include <mizuiro/access/raw.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace image
{
namespace view
{

template<
	typename Color,
	typename Dim,
	typename Constness
>
struct mizuiro_type
{
	typedef mizuiro::image::view<
		mizuiro::access::raw,
		mizuiro::image::format<
			mizuiro::image::dimension<
				Dim::value
			>,
			mizuiro::image::interleaved<
				Color
			>
		>,
		Constness
	> type;
};

}
}
}

#endif
