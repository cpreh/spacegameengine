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


#ifndef SGE_RENDERER_IMAGE_HPP_INCLUDED
#define SGE_RENDERER_IMAGE_HPP_INCLUDED

#include "color.hpp"
#include <boost/gil/image.hpp>
#include <boost/gil/extension/dynamic_image/any_image.hpp>
#include <boost/mpl/vector.hpp>

namespace sge
{
namespace renderer
{

typedef boost::gil::image<
	rgba8_pixel,
	false
> rgba8_image;

typedef boost::gil::image<
	argb8_pixel,
	false
> argb8_image;

typedef boost::gil::any_image<
	boost::mpl::vector<
		rgba8_image,
		argb8_image
	>
> image;

}
}


#endif
