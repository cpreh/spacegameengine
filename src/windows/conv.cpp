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


#include <sge/windows/conv.hpp>
#include <sge/codecvt.hpp>

//#ifdef SGE_NARROW_STRING
sge::win_string sge::sge_str_to_win(string const &in)
{
	return in;
}

sge::string sge::win_str_to_sge(win_string const &in)
{
	return in;
}
/*#else
sge::win_string sge::sge_str_to_win(const string& in)
{
	return widen(in);
}

sge::string sge::win_str_to_sge(const win_string& in)
{
	return narrow(in);
}
#endif*/
