/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FONT_IMAGE_VIEW_HPP_INCLUDED
#define SGE_FONT_IMAGE_VIEW_HPP_INCLUDED

#include <sge/font/color.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/step_iterator.hpp>

namespace sge
{
namespace font
{

// TODO: make a helper class for this

typedef boost::gil::image_view<
	boost::gil::memory_based_2d_locator<
		boost::gil::memory_based_step_iterator<
			color *
		>
	>
> image_view;

typedef image_view::const_t const_image_view;

}
}

#endif
