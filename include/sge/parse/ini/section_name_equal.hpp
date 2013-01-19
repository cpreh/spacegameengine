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


#ifndef SGE_PARSE_INI_SECTION_NAME_EQUAL_HPP_INCLUDED
#define SGE_PARSE_INI_SECTION_NAME_EQUAL_HPP_INCLUDED

#include <sge/parse/symbol.hpp>
#include <sge/parse/ini/section_fwd.hpp>
#include <sge/parse/ini/section_name.hpp>


namespace sge
{
namespace parse
{
namespace ini
{

class section_name_equal
{
public:
	typedef bool result_type;

	SGE_PARSE_SYMBOL
	explicit
	section_name_equal(
		sge::parse::ini::section_name const &
	);

	SGE_PARSE_SYMBOL
	result_type
	operator()(
		sge::parse::ini::section const &
	) const;
private:
	sge::parse::ini::section_name name_;
};

}
}
}

#endif
