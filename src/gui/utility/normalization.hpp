/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#ifndef SGE_GUI_UTILITY_NORMALIZATION_HPP_INCLUDED
#define SGE_GUI_UTILITY_NORMALIZATION_HPP_INCLUDED

#include <limits>

namespace sge
{
namespace gui
{
namespace utility
{
template<typename Dest,typename Src>
Dest normalize(Src const &s)
{
	return static_cast<Dest>(
		(static_cast<Dest>(s) - static_cast<Dest>(std::numeric_limits<Src>::min()))/
		(static_cast<Dest>(static_cast<Dest>(std::numeric_limits<Src>::max()) - static_cast<Dest>(std::numeric_limits<Src>::min()))));
}

template<typename Dest,typename Src>
Dest denormalize(Src const &s)
{
	return static_cast<Dest>(
		s*static_cast<Src>(static_cast<Src>(std::numeric_limits<Dest>::max())-static_cast<Src>(std::numeric_limits<Dest>::min()))+static_cast<Src>(std::numeric_limits<Dest>::min()));
}
}
}
}

#endif
