/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


//                  encoding enum         windows          linux
SGE_ICONV_ENCODING3( enc_ascii,           ISO-8859-1,      ASCII     ),
SGE_ICONV_ENCODING3( enc_string_literal,  CP1252,          UTF-8     ),
SGE_ICONV_ENCODING3( enc_wstring_literal, UTF-16,          UTF32LE   ),
SGE_ICONV_ENCODING2( enc_utf8,            UTF-8                      ),
SGE_ICONV_ENCODING2( enc_utf16,           UTF-16                     ),
SGE_ICONV_ENCODING3( enc_ucs_4_internal,  UTF-32LE,        UTF32LE   )
