/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_EXTRA_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_EXTRA_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/element_count_type.hpp>
#include <sge/renderer/vf/vector.hpp>
#include <sge/renderer/vf/dynamic/detail/make_color.hpp>
#include <sge/renderer/vf/dynamic/detail/make_vector.hpp>
#include <mizuiro/color/format/homogenous_static_fwd.hpp>


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
	typename Format,
	sge::renderer::vf::element_count_type NumSubElements
>
inline
sge::renderer::vf::dynamic::vector
make_extra_element(
	sge::renderer::vf::vector<
		Format,
		NumSubElements
	> const &
)
{
	return
		sge::renderer::vf::dynamic::detail::make_vector<
			Format,
			NumSubElements
		>();
}

template<
	typename ColorChannel,
	typename ColorLayout
>
inline
sge::renderer::vf::dynamic::color
make_extra_element(
	mizuiro::color::format::homogenous_static<
		ColorChannel,
		ColorLayout
	> const  &
)
{
	return
		sge::renderer::vf::dynamic::detail::make_color<
			mizuiro::color::format::homogenous_static<
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
