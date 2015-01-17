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


#ifndef SGE_SRC_RENDERER_INDEX_DYNAMIC_FORMAT_ENUM_STATIC_HPP_INCLUDED
#define SGE_SRC_RENDERER_INDEX_DYNAMIC_FORMAT_ENUM_STATIC_HPP_INCLUDED

#include <sge/renderer/index/format_is_16.hpp>
#include <sge/renderer/index/format_is_32.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace dynamic
{
namespace
{

template<
	typename Format,
	typename Enable = void
>
struct format_enum_static;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format
>
struct format_enum_static<
	Format,
	typename boost::enable_if<
		sge::renderer::index::format_is_16<
			Format
		>
	>::type
>
:
std::integral_constant<
	sge::renderer::index::dynamic::format,
	sge::renderer::index::dynamic::format::i16
>
{
};

template<
	typename Format
>
struct format_enum_static<
	Format,
	typename boost::enable_if<
		sge::renderer::index::format_is_32<
			Format
		>
	>::type
>
:
std::integral_constant<
	sge::renderer::index::dynamic::format,
	sge::renderer::index::dynamic::format::i32
>
{
};

FCPPT_PP_POP_WARNING

}
}
}
}
}

#endif
