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


#ifndef SGE_IMAGE_COLOR_ANY_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_COLOR_ANY_ELEMENTS_HPP_INCLUDED

#include <sge/image/color/gray8.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/argb8.hpp>
#include <sge/image/color/bgra8.hpp>
#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/argb32f.hpp>
#include <sge/image/color/bgra32f.hpp>
#include <boost/mpl/vector.hpp>

namespace sge
{
namespace image
{
namespace color
{
namespace any
{

typedef boost::mpl::vector<
	gray8,
	rgba8,
	argb8,
	bgra8,
	rgba32f,
	argb32f,
	bgra32f
> elements;

}
}
}
}

#endif
