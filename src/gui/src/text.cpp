/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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

#include "../text.hpp"

namespace {
	class gui_text_drawer {
		sge::gui::text &text_;
	public:
		gui_text_drawer(sge::gui:text &text_)
		: text_(text_) {}

		void begin_rendering(const size_type numglyphs, const font_dim dimensions) {
			text_.resize(sge::gui::dim2(dimensions[0], dimensions[1]));
			text_.glyphpositions.clear();
			text_.glyphpositions.reserve(numglyphs);
		}

		void draw_char(const font_char ch, const font_rect fr, const font_color* const data) {

			for (const font_color *b = data, e = b + (fr.right-fr.left) * (fr.top-fr.bottom)
		}

		void end_rendering() {}
	};
}


