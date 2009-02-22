/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_MAKE_DYNAMIC_ELEMENTS_HPP_INCLUDED
#define SGE_RENDERER_VF_MAKE_DYNAMIC_ELEMENTS_HPP_INCLUDED

#include <sge/renderer/vf/dynamic_element_list.hpp>
#include <sge/renderer/vf/dynamic_format.hpp>
#include <sge/renderer/vf/role.hpp>
#include <sge/renderer/vf/format_to_element.hpp>
#include <sge/renderer/vf/color_base.hpp>
#include <sge/renderer/vf/vec_base.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/color_format_static.hpp>
#include <map>

namespace sge
{
namespace renderer
{
namespace vf
{

struct make_dynamic_elements {
	explicit make_dynamic_elements(
		dynamic_element_list &elems)
	:
		elems(elems)
	{}

	template<
		typename Format,
		role::type Role,
		vertex_size NumSubElements
	>
	void operator()(
		vec_base<
			Format,
			Role,
			NumSubElements
		> &) const
	{
		elems.push_back(
			dynamic_element(
				dynamic_vector(
					format_to_element<
						Format
					>::value,
					NumSubElements
				),
				Role,
				category_count[Role]++
			));
	}

	template<
		typename Format,
		role::type Role
	>
	void operator()(
		color_base<
			Format,
			Role
		> &) const
	{
		elems.push_back(
			dynamic_element(
				dynamic_color(
					color_format_static<Format>::value
				),
				Role,
				category_count[Role]++
			));
	}
private:
	dynamic_element_list &elems;
	
	typedef std::map<
		role::type,
		vertex_size
	> category_count_map;

	mutable category_count_map category_count;
};

}
}
}

#endif
