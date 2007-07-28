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


#include "../check_box.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::check_box::check_box(manager& man, element* const parent, const string& _text, const point pos, const dim sz, const color _text_color, const bool v, const bool visible, const bool enabled)
: rectangle(man, parent, pos, sz, skin::checkbox_name, visible, enabled),
  _text(_text), _text_color(_text_color),
  box(man,this, point(0, unit(0.5) * sz.h() - unit(0.5) * click_box::sz.h()), click_box::quad, v)
{}

void sge::gui::check_box::on_draw(const draw_event& event)
{
	rectangle::on_draw(event);
	const dim cbsz(box.width(),0);
	m.get_font().draw_text(_text, event.pos() + point(cbsz.w(), cbsz.h()), size() - cbsz, _text_color, font_flags::align_left | font_flags::align_vcenter);
}

bool sge::gui::check_box::value() const
{
	return box.value();
}

void sge::gui::check_box::text(const string& t)
{
	_text = t;
}

const sge::string& sge::gui::check_box::text() const
{
	return _text;
}

void sge::gui::check_box::text_color(const color c)
{
	_text_color = c;
}

sge::color sge::gui::check_box::text_color() const
{
	return _text_color;
}
