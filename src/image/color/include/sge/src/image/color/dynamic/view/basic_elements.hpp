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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_VIEW_BASIC_ELEMENTS_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_VIEW_BASIC_ELEMENTS_HPP_INCLUDED

#include <sge/image/integral_size.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/view/make_mizuiro_type.hpp>
#include <sge/src/image/color/dynamic/format/all.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{
namespace view
{

template<
	sge::image::size_type Dim,
	typename Constness
>
using basic_elements
=
typename
boost::mpl::transform<
	sge::image::color::dynamic::format::all,
	sge::image::view::make_mizuiro_type<
		boost::mpl::_1,
		sge::image::integral_size<
			Dim
		>,
		Constness
	>
>::type;

}
}
}
}
}

#endif
