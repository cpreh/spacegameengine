/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_ICONV_TYPES_HPP_INCLUDED
#define SGE_ICONV_TYPES_HPP_INCLUDED

#include <stdexcept>
#include <string>

namespace sge
{

enum encoding {
	enc_ascii,
	enc_char_locale,
	enc_utf8,
	enc_utf16,
	enc_ucs_4_internal
};

class invalid_conversion : public std::runtime_error {
public:
	invalid_conversion(const std::string& from, const std::string& to)
	: std::runtime_error(std::string("Unsupported conversion from ") += from + " to " + to + "!" ) {}
};

class conversion_failed : public std::runtime_error {
public:
	conversion_failed()
	: std::runtime_error("An iconv conversion failed!") {}
};

}

#endif
