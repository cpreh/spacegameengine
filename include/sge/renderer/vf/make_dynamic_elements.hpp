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

#include "dynamic_element_list.hpp"
#include "dynamic_format.hpp"
#include "role.hpp"
#include "format_to_element.hpp"
#include "color_base.hpp"
#include "vec_base.hpp"
#include "../color_format_static.hpp"

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
				Role
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
				Role
			));
	}
private:
	dynamic_element_list &elems;
};

}
}
}

#endif
