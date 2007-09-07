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


#include "../static_text.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::static_text::static_text(manager& m, element* const parent, const string& _text, const point pos, const dim sz, const color _text_color, const bool visible, const bool enabled)
:  rectangle(m, parent, pos, sz, texture_map::no_texture, visible, enabled),
   _text(_text),
   _text_color(_text_color),
   _style(font_flags::default_)
{}

void sge::gui::static_text::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
	m.get_font().draw_text(text(), event.pos(), size(), text_color(), style());
}


const sge::string& sge::gui::static_text::text() const
{
	return _text;
}

void sge::gui::static_text::text(const string& t)
{
	_text = t;
}

sge::color sge::gui::static_text::text_color() const
{
	return _text_color;
}

void sge::gui::static_text::text_color(const color c)
{
	_text_color = c;
}

sge::font_flag_t sge::gui::static_text::style() const
{
	return _style;
}

void sge::gui::static_text::style(const font_flag_t s)
{
	_style = s;
}
