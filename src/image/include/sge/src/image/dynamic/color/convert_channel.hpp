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


#ifndef SGE_SRC_IMAGE_DYNAMIC_COLOR_CONVERT_CHANNEL_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_COLOR_CONVERT_CHANNEL_HPP_INCLUDED

#include <sge/src/image/dynamic/color/available_channels.hpp>
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

#define SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CONVERT_CHANNEL(\
	channel_name\
)\
inline \
sge::image::dynamic::color::available_channels::type \
convert_channel( \
	mizuiro::color::channel::channel_name const &\
)\
{\
	return \
		sge::image::dynamic::color::available_channels::channel_name;\
}

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CONVERT_CHANNEL(
	alpha
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CONVERT_CHANNEL(
	blue
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CONVERT_CHANNEL(
	green
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CONVERT_CHANNEL(
	luminance
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CONVERT_CHANNEL(
	red
)

SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CONVERT_CHANNEL(
	undefined
)

#undef SGE_SRC_IMAGE_DYNAMIC_COLOR_MAKE_CONVERT_CHANNEL

}
}
}
}

#endif
