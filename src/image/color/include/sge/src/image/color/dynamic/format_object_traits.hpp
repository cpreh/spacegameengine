/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_TRAITS_HPP_INCLUDED
#define SGE_SRC_IMAGE_COLOR_DYNAMIC_FORMAT_OBJECT_TRAITS_HPP_INCLUDED

#include <sge/src/image/color/dynamic/format_object_fwd.hpp>
#include <mizuiro/color/format/tag_of_fwd.hpp>
#include <mizuiro/color/format/homogenous_dynamic_ns/tag.hpp>


namespace mizuiro
{
namespace color
{
namespace format
{

template<
	typename BaseType,
	unsigned NumChannels
>
struct tag_of<
	sge::image::color::dynamic::format_object<
		BaseType,
		NumChannels
	>
>
{
	typedef
	mizuiro::color::format::homogenous_dynamic_ns::tag<
		sge::image::color::dynamic::format_object<
			BaseType,
			NumChannels
		>
	>
	type;
};

}
}
}

#endif
