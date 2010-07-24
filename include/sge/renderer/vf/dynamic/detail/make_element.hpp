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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/detail/make_vector.hpp>
#include <sge/renderer/vf/dynamic/detail/make_color.hpp>
#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/vf/dynamic/normal.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/texpos.hpp>
#include <sge/renderer/vf/dynamic/unspecified.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/normal.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/texpos.hpp>
#include <sge/renderer/vf/unspecified.hpp>
#include <sge/renderer/vf/vertex_size.hpp>

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
	vertex_size NumSubElements
>
dynamic::element const
make_element(
	vf::pos<
		Format,
		NumSubElements
	> const &
)
{
	return
		element(
			dynamic::pos(
				detail::make_vector<
					Format,
					NumSubElements
				>()
			)
		);
}

template<
	typename Format
>
dynamic::element const
make_element(
	vf::normal<
		Format,
		NumSubelements
	> const &
)
{
	return
		elements(
			dynamic::normal(
				NumSubElements
			)
		);
}

template<
	typename Format
>
dynamic::element const
make_element(
	vf::color<
		Format
	> const &
) const
{
	return
		element(
			detail::make_color<
				Format
			>()
		);
}

template<
	typename Format,
	vertex_size NumSubElements,
	typename Index
>
dynamic::element const 
make_element(
	vf::texpos<
		Format,
		NumSubElements
	> const &
)
{
	return
		element(
			dynamic::texpos(
				detail::format_to_element<
					Format
				>::value,
				NumSubElements,
				Index::value
			)
		);
}

template<
	typename Format,
	vertex_size NumSubElements,
	typename Tag
>
dynamic::element const
operator()(
	vf::unspecified<
		Format,
		NumSubElements,
		Tag
	> const &
)
{
	// !
}

}
}
}
}
}

#endif
