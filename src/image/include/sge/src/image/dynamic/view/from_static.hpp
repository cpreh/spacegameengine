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


#ifndef SGE_SRC_IMAGE_DYNAMIC_VIEW_FROM_STATIC_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_VIEW_FROM_STATIC_HPP_INCLUDED

#include <sge/image/view/element_base.hpp>
#include <sge/src/image/dynamic/color/from_static_format.hpp>
#include <sge/src/image/dynamic/color/from_static_format_type.hpp>


namespace sge
{
namespace image
{
namespace dynamic
{
namespace view
{

template<
	typename View
>
typename sge::image::view::element_base<
	typename dynamic::color::from_static_format_type<
		typename View::format::color_format
	>::type,
	View::dim::static_size,
	typename View::constness
>::type
from_static(
	View const &_view
)
{
	typedef typename sge::image::view::element_base<
		typename dynamic::color::from_static_format_type<
			typename View::format::color_format
		>::type,
		View::dim::static_size,
		typename View::constness
	>::type dest_type;

	typedef typename dest_type::format dest_format;

	return
		dest_type(
			_view.size(),
			_view.data(),
			_view.pitch(),
			typename dest_type::format_store_type(
				dest_format(
					typename dest_format::color_format_store_type(
						dynamic::color::from_static_format(
							typename View::format::color_format()
						)
					)
				)
			)
		);
}

}
}
}
}

#endif
