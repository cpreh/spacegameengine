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

#include <cassert>
#include <cstring>

#include "../../renderer/font_drawer.hpp"
#include "../../renderer/font.hpp"
#include "../text.hpp"

namespace sge {
namespace gui {
	class gui_text_drawer : public sge::font_drawer {
		sge::gui::text &text_;
	public:
		gui_text_drawer(sge::gui::text &text_)
		: text_(text_) {}

		void begin_rendering(const sge::font::size_type numglyphs, const sge::font_dim dimensions) {
			text_.resize(sge::gui::dim2(dimensions[0], dimensions[1]));

			text_.glyphpositions.clear();
			text_.glyphpositions.reserve(numglyphs);

			text_.glyphs.clear();
			text_.glyphs.reserve(numglyphs);
		}

		void draw_char(const sge::font_char ch, const sge::font_rect fr, const sge::font_color* const data) {
			assert(fr.right >= fr.left);
			assert(fr.top >= fr.bottom);
			sge::gui::rect rect(fr.left, fr.top, fr.right-fr.left, fr.bottom-fr.top);
			unsigned int y = 0;
			for (const font_color *b = data, *e = b + rect.w * rect.h; b != e; b += rect.w) {
				std::memcpy(
					text_.data.get() + (y++ + rect.y) * text_.size().w + rect.x,
					b,
					rect.w
				);

				text_.glyphs        .push_back(ch);
				text_.glyphpositions.push_back(rect);
			}
		}

		void end_rendering() {}
	};
}
}

