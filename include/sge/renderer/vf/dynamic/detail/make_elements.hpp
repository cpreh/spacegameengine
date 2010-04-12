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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_ELEMENTS_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_ELEMENTS_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/detail/format_to_element.hpp>
#include <sge/renderer/vf/dynamic/element_list.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/role.hpp>
#include <sge/renderer/vf/color_base.hpp>
#include <sge/renderer/vf/vec_base.hpp>
#include <sge/renderer/vf/single_base.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/image/color/format_static.hpp>
#include <map>

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

class make_elements
{
public:
	explicit make_elements(
		element_list &elems
	)
	:
		elems(elems)
	{}

	typedef void result_type;

	template<
		typename Format,
		role::type Role,
		vertex_size NumSubElements
	>
	result_type
	operator()(
		vec_base<
			Format,
			Role,
			NumSubElements
		> &
	) const
	{
		elems.push_back(
			element(
				vector(
					detail::format_to_element<
						Format
					>::value,
					NumSubElements
				),
				Role,
				make_category_count<
					Role
				>()
			)
		);
	}

	template<
		typename Format,
		role::type Role
	>
	result_type
	operator()(
		color_base<
			Format,
			Role
		> &
	) const
	{
		elems.push_back(
			element(
				color(
					image::color::format_static<Format>::value
				),
				Role,
				make_category_count<
					Role
				>()
			)
		);
	}

	template<
		typename Format,
		role::type Role
	>
	result_type
	operator()(
		single_base<
			Format,
			Role
		> &
	) const
	{
		vec_base<
			Format,
			Role,
			1u
		> base;

		return
			(*this)(
				base
			);
	}
private:
	template<
		role::type Role
	>
	vertex_size
	make_category_count() const
	{
		return category_count[Role]++;
	}

	element_list &elems;

	typedef std::map<
		role::type,
		vertex_size
	> category_count_map;

	mutable category_count_map category_count;
};

}
}
}
}
}

#endif
