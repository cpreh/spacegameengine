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


#ifndef SGE_CHARCONV_CONVERT_HPP_INCLUDED
#define SGE_CHARCONV_CONVERT_HPP_INCLUDED

#include <sge/charconv/encoding_fwd.hpp>
#include <sge/charconv/string_type.hpp>
#include <sge/charconv/detail/symbol.hpp>


namespace sge
{
namespace charconv
{

template<
	sge::charconv::encoding DestEncoding,
	sge::charconv::encoding SourceEncoding
>
SGE_CHARCONV_DETAIL_SYMBOL
sge::charconv::string_type<
	DestEncoding
>
convert(
	sge::charconv::string_type<
		SourceEncoding
	> const &
);

}
}

#endif
