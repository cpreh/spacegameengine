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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_FORMAT_TO_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_FORMAT_TO_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/detail/element_c.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


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
	typename Type
>
struct format_to_element;

#define SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(\
	type_arg,\
	value_arg\
)\
template<>\
struct format_to_element<\
	type_arg\
>\
:\
sge::renderer::vf::dynamic::detail::element_c<\
	sge::renderer::vf::dynamic::element_type::value_arg\
>\
{\
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	float,
	float_
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	double,
	double_
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	char,
	byte
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	unsigned char,
	ubyte
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	short,
	short_
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	unsigned short,
	ushort
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	int,
	int_
);

SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT(
	unsigned,
	uint
);

FCPPT_PP_POP_WARNING

#undef SGE_RENDERER_VF_DYNAMIC_DETAIL_MAKE_FORMAT_TO_ELEMENT

}
}
}
}
}

#endif
