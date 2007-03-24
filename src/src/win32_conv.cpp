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


#include "../win32_conv.hpp"
#include "../detail/iconv_detail.hpp"
#include "../iconv_types.hpp"

const sge::encoding enc_win = 
#ifdef UNICODE
sge::enc_utf16
#else
sge::enc_ascii
#endif
;

sge::win_string sge::sge_str_to_win(const string& in)
{
	return _iconv<win_string>(in, enc_ucs_4_internal, enc_win, in.get_allocator());
}

sge::string sge::win_str_to_sge(const win_string& in)
{
	return _iconv<string>(in, enc_win, enc_ucs_4_internal, in.get_allocator());
}
