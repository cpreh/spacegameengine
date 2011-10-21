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


#ifndef SGE_RENDERER_INDEX_DYNAMIC_FORMAT_ENUM_STATIC_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_FORMAT_ENUM_STATIC_HPP_INCLUDED

#include <sge/renderer/index/format_is_16.hpp>
#include <sge/renderer/index/format_is_32.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
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

template<
	typename Format
>
struct format_enum_static<
	Format,
	typename boost::enable_if<
		index::format_is_16<
			Format
		>
	>::type
>
:
boost::mpl::integral_c<
	format::type,
	format::i16
>
{};

template<
	typename Format
>
struct format_enum_static<
	Format,
	typename boost::enable_if<
		index::format_is_32<
			Format
		>
	>::type
>
:
boost::mpl::integral_c<
	format::type,
	format::i32
>
{};

}
}
}
}
}

#endif
