/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PARSE_INI_GET_OR_CREATE_HPP_INCLUDED
#define SGE_PARSE_INI_GET_OR_CREATE_HPP_INCLUDED

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/start_fwd.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/parse/ini/detail/symbol.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

SGE_PARSE_INI_DETAIL_SYMBOL
sge::parse::ini::value
get_or_create(
	sge::parse::ini::start &,
	sge::parse::ini::section_name const &,
	sge::parse::ini::entry_name const &,
	sge::parse::ini::value const &
);

}
}
}

#endif
