/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CONSOLE_EXCEPTION_HPP_INCLUDED
#define SGE_CONSOLE_EXCEPTION_HPP_INCLUDED

#include <sge/core/exception.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <sge/console/detail/symbol.hpp>
#include <sge/font/string.hpp>


namespace sge
{
namespace console
{

class SGE_CORE_DETAIL_CLASS_SYMBOL exception
:
	public sge::core::exception
{
public:
	SGE_CONSOLE_DETAIL_SYMBOL
	explicit
	exception(
		sge::font::string const &
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	~exception() throw()
	override;

	SGE_CONSOLE_DETAIL_SYMBOL
	sge::font::string const &
	console_string() const;
private:
	sge::font::string console_string_;
};

}
}

#endif
