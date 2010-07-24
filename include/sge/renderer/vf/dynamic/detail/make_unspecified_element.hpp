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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_UNSPECIFIED_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_UNSPECIFIED_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/detail/make_vector.hpp>
#include <sge/renderer/vf/dynamic/detail/make_color.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <mizuiro/color/homogenous_fwd.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{
namespace detail
{

template<
	typename Format
>
dynamic::vector const
make_unspecified_element(
	Format const &
)
{
	return
		detail::make_vector<
			Format,
			1
		>();
}

template<
	typename Format,
	vertex_size NumSubElements
>
dynamic::vector const
make_unspecified_element(
	vf::vector<
		Format,
		NumSubElements
	> const &
)
{
	return
		detail::make_vector<
			Format,
			NumSubElements
		>();
}

template<
	typename ColorChannel,
	typename ColorLayout
>
dynamic::color const
make_unspecified_element(
	mizuiro::color::homogenous<
		ColorChannel,
		ColorLayout
	> const  &
)
{
	return
		detail::make_color<
			mizuiro::color::homogenous<
				ColorChannel,
				ColorLayout
			> 		
		>();
}

}
}
}
}
}

#endif
