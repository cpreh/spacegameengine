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


#ifndef SGE_SRC_IMAGE_DYNAMIC_COLOR_CHANNEL_INDEX_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_COLOR_CHANNEL_INDEX_HPP_INCLUDED

#include <mizuiro/size_type.hpp>
#include <mizuiro/color/channel/alpha.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/luminance.hpp>
#include <mizuiro/color/channel/red.hpp>


namespace sge
{
namespace image
{
namespace dynamic
{
namespace color
{

#define SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CHANNEL_INDEX(\
	Channel,\
	index\
)\
inline \
mizuiro::size_type \
channel_index( \
	Channel const &\
)\
{\
	return index;\
}

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CHANNEL_INDEX(
	mizuiro::color::channel::alpha,
	0
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CHANNEL_INDEX(
	mizuiro::color::channel::blue,
	1
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CHANNEL_INDEX(
	mizuiro::color::channel::green,
	2
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CHANNEL_INDEX(
	mizuiro::color::channel::luminance,
	3
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CHANNEL_INDEX(
	mizuiro::color::channel::red,
	4
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CHANNEL_INDEX(
	mizuiro::color::channel::undefined,
	5
)

#undef SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CHANNEL_INDEX

}
}
}
}

#endif
