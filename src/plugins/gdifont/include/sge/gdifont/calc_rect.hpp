/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GDIFONT_CALC_RECT_HPP_INCLUDED
#define SGE_GDIFONT_CALC_RECT_HPP_INCLUDED

#include <sge/font/align_h.hpp>
#include <sge/font/optional_unit_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/format.hpp>


namespace sge
{
namespace gdifont
{

sge::font::rect const
calc_rect(
	sge::gdifont::device_context const &,
	sge::font::string const &,
	sge::font::align_h::type,
	sge::font::optional_unit const &max_width,
	sge::gdifont::format
);

}
}

#endif
