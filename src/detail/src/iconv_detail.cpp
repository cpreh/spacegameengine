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


#include <stdexcept>
#include "../iconv_detail.hpp"
#include "../../iconv_types.hpp"

sge::iconv_instance::iconv_instance(const std::string &from, const std::string &to) 
: conv(iconv_open(to.c_str(), from.c_str())),
  from(from),
  to(to)
{
	if(conv == reinterpret_cast<iconv_t>(-1))
		throw sge::invalid_conversion(from,to);
}

sge::iconv_instance::~iconv_instance()
{
	iconv_close(conv);
}

std::size_t sge::iconv_instance::convert(const char **inbuf, std::size_t *inbytes, char **outbuf, std::size_t *outbytes)
{
	std::size_t bytesread = *inbytes;
	const std::size_t result = iconv(conv, const_cast<char**>(inbuf), inbytes, outbuf, outbytes);
	if(result == static_cast<std::size_t>(-1))
	{
		switch(errno) {
		case E2BIG:
			break;
		default:
			throw sge::conversion_failed(from,to);
		}
	}
	return bytesread - *inbytes;
}

std::string sge::encoding_to_string(const sge::encoding& to)
{
	switch(to) {
	case enc_string_literal:
#ifdef _MSC_VER
		return "CP1252";
#elif __GNUC__
		return "UTF-8";
#else
#error "implement me!"
#endif
	case enc_wstring_literal:
#ifdef _MSC_VER
		return "UTF-16";
#elif __GNUC__
		return "UTF-32";
#else
#error "implement me!"
#endif
	case enc_utf8:
		return "UTF-8";
	case enc_ucs_4_internal:
		return "UCS-4";
	case enc_utf16:
		return "UTF-16";
	case enc_ascii:
		return "ASCII";
	default:
		throw std::logic_error("Invalid encoding!");
	}
}
