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


#ifndef SGE_CHARCONV_UNSUPPORTED_CONVERSION_HPP_INCLUDED
#define SGE_CHARCONV_UNSUPPORTED_CONVERSION_HPP_INCLUDED

#include <sge/charconv/exception.hpp>
#include <sge/charconv/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace charconv
{

class SGE_CLASS_SYMBOL unsupported_conversion
:
	public sge::charconv::exception
{
public:
	SGE_CHARCONV_SYMBOL
	unsupported_conversion(
		fcppt::string const &source,
		fcppt::string const &dest
	);

	SGE_CHARCONV_SYMBOL
	~unsupported_conversion() throw();

	SGE_CHARCONV_SYMBOL
	fcppt::string const &
	source() const;

	SGE_CHARCONV_SYMBOL
	fcppt::string const &
	dest() const;
private:
	fcppt::string
		source_,
		dest_;
};

}
}

#endif
