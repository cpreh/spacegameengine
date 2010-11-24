/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_ICONV_UNSUPPORTED_CONVERSION_HPP_INCLUDED
#define SGE_ICONV_UNSUPPORTED_CONVERSION_HPP_INCLUDED

#include <sge/iconv/charset_string.hpp>
#include <sge/iconv/symbol.hpp>
#include <sge/iconv/exception.hpp>
#include <sge/class_symbol.hpp>

namespace sge
{
namespace iconv
{

class SGE_CLASS_SYMBOL unsupported_conversion
:
	public sge::iconv::exception
{
public:
	SGE_ICONV_SYMBOL
	unsupported_conversion(
		iconv::charset_string const &source,
		iconv::charset_string const &dest
	);

	SGE_ICONV_SYMBOL
	~unsupported_conversion() throw();

	SGE_ICONV_SYMBOL
	iconv::charset_string const &
	source() const;

	SGE_ICONV_SYMBOL
	iconv::charset_string const &
	dest() const;
private:
	iconv::charset_string
		source_,
		dest_;
};

}
}

#endif
