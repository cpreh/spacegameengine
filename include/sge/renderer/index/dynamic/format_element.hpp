/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_INDEX_DYNAMIC_FORMAT_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_FORMAT_ELEMENT_HPP_INCLUDED

#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <sge/renderer/index/dynamic/format.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace dynamic
{

template<
	sge::renderer::index::dynamic::format
>
struct format_element;

template<>
struct format_element<
	sge::renderer::index::dynamic::format::i16
>
{
	typedef
	sge::renderer::index::i16
	type;
};

template<>
struct format_element<
	sge::renderer::index::dynamic::format::i32
>
{
	typedef
	sge::renderer::index::i32
	type;
};

}
}
}
}

#endif
