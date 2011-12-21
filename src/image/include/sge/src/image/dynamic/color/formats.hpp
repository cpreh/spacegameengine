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


#ifndef SGE_SRC_IMAGE_DYNAMIC_COLOR_FORMATS_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_COLOR_FORMATS_HPP_INCLUDED

#include <sge/src/image/dynamic/color/c32f_1_format.hpp>
#include <sge/src/image/dynamic/color/c32f_3_format.hpp>
#include <sge/src/image/dynamic/color/c32f_4_format.hpp>
#include <sge/src/image/dynamic/color/c8_1_format.hpp>
#include <sge/src/image/dynamic/color/c8_2_format.hpp>
#include <sge/src/image/dynamic/color/c8_3_format.hpp>
#include <sge/src/image/dynamic/color/c8_4_format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace dynamic
{
namespace color
{

typedef boost::mpl::vector7<
	dynamic::color::c8_1_format,
	dynamic::color::c8_2_format,
	dynamic::color::c8_3_format,
	dynamic::color::c8_4_format,
	dynamic::color::c32f_1_format,
	dynamic::color::c32f_3_format,
	dynamic::color::c32f_4_format
> formats;

}
}
}
}

#endif
