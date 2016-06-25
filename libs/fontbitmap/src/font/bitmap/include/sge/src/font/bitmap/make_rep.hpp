/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_FONT_BITMAP_MAKE_REP_HPP_INCLUDED
#define SGE_SRC_FONT_BITMAP_MAKE_REP_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <sge/src/font/bitmap/line_height.hpp>
#include <sge/src/font/bitmap/rep.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{

sge::font::bitmap::rep
make_rep(
	sge::font::bitmap::char_map const &,
	sge::font::bitmap::line_height,
	sge::font::string const &,
	sge::font::text_parameters const &
);

}
}
}

#endif
