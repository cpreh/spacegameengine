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


#ifndef SGE_SRC_FONT_BITMAP_TEXT_HPP_INCLUDED
#define SGE_SRC_FONT_BITMAP_TEXT_HPP_INCLUDED

#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{

class text
:
	public sge::font::text
{
	FCPPT_NONCOPYABLE(
		text
	);
public:
	text(
		sge::font::bitmap::char_map &,
		sge::font::string const &,
		sge::font::text_parameters const &
	);

	~text();
private:
	void
	render(
		sge::font::view const &
	);

	sge::font::rect const
	rect();

	sge::font::bitmap::char_map &char_map_;

	sge::font::string const string_;

	sge::font::text_parameters const text_parameters_;
};

}
}
}

#endif
