/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_VIEW_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_VIEW_ELEMENTS_HPP_INCLUDED

#include <sge/image/color/any/elements.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/step_iterator.hpp>

namespace sge
{
namespace image
{
namespace view
{
// TODO: move to detail!
namespace detail
{

template<
	typename Color
>
struct view_type {
	typedef boost::gil::image_view<
		boost::gil::memory_based_2d_locator<
			boost::gil::memory_based_step_iterator<
				Color *
			>
		>
	> type;
};

}

typedef boost::mpl::transform<
	color::any::elements,
	detail::view_type<
		boost::mpl::placeholders::_1
	>
>::type elements;

}
}
}

#endif
