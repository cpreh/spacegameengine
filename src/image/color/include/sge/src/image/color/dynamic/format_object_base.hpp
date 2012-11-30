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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_BASE_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_BASE_HPP_INCLUDED

#include <sge/src/image/color/dynamic/available_channels.hpp>
#include <mizuiro/color/homogenous_dynamic_fwd.hpp>
#include <mizuiro/color/access/homogenous_dynamic.hpp>
#include <mizuiro/color/types/homogenous.hpp>
#include <mizuiro/color/types/homogenous_dynamic.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace dynamic
{

template<
	typename BaseType,
	unsigned NumChannels
>
struct format_object_base
{
	typedef mizuiro::color::homogenous_dynamic<
		BaseType,
		sge::image::color::dynamic::available_channels::type,
		sge::image::color::dynamic::available_channels::size,
		NumChannels
	> type;
};

}
}
}
}

#endif
