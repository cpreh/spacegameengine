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


#ifndef SGE_RENDERER_VF_DYNAMIC_DETAIL_FORMAT_TO_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_DETAIL_FORMAT_TO_ELEMENT_HPP_INCLUDED

#include <sge/renderer/vf/element_type.hpp>
#include <sge/renderer/vf/dynamic/detail/element_c.hpp>


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
	typename T
>
struct format_to_element;

template<>
struct format_to_element<
	float
>
:
element_c<
	element_type::float_
>
{};

template<>
struct format_to_element<
	double
>
:
element_c<
	element_type::double_
>
{};

template<>
struct format_to_element<
	char
>
:
element_c<
	element_type::byte
>
{};

template<>
struct format_to_element<
	unsigned char
>
:
element_c<
	element_type::ubyte
>
{};

template<>
struct format_to_element<
	short
>
:
element_c<
	element_type::short_
>
{};

template<>
struct format_to_element<
	unsigned short
>
:
element_c<
	element_type::ushort
>
{};

template<>
struct format_to_element<
	int
>
:
element_c<
	element_type::int_
>
{};

template<>
struct format_to_element<
	unsigned
>
:
element_c<
	element_type::uint
>
{};

}
}
}
}
}

#endif
