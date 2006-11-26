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


#include "../static_text.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::static_text::static_text(manager& m, element* const parent, const string& _text, const point pos, const dim sz, const color _text_color, const bool visible, const bool enabled)
:  rectangle(m, parent, pos, sz, skin::statictext_name, visible, enabled),
   _text(_text),
   _text_color(_text_color)
{}

void sge::gui::static_text::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
	m.get_font().height(height()/2); // FIXME
	m.get_font().draw_text(_text, event.pos(), size(), _text_color);
}
