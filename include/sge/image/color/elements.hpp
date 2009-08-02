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


#ifndef SGE_IMAGE_COLOR_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_COLOR_ELEMENTS_HPP_INCLUDED

#include <sge/image/color/gray8_format.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/argb8_format.hpp>
#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/argb32f_format.hpp>
#include <sge/image/color/bgra32f_format.hpp>
#include <boost/mpl/vector.hpp>

namespace sge
{
namespace image
{
namespace color
{

typedef boost::mpl::vector<
	gray8_format,
	rgba8_format,
	argb8_format,
	bgra8_format,
	rgba32f_format,
	argb32f_format,
	bgra32f_format
> elements;

}
}
}

#endif
