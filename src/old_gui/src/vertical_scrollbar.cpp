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


#include "../vertical_scrollbar.hpp"
#include "../manager.hpp"
#include "../skin.hpp"
#include <boost/bind.hpp>

sge::gui::vertical_scrollbar::vertical_scrollbar(manager& m, element* const parent, const point pos, const dim sz, const bool visible, const bool enabled)
: rectangle(m,parent,pos,sz,skin::scrollbar_name,visible,enabled),
  s_pos(0),
  s_max(0),
  scrollbar(m, this, point(0, sz.w()), dim(sz.w(), sz.h() - 2*sz.w())),
  up_scroll_button(m, this, point(0,0), dim(sz.w(), sz.w()), scroll_button::up_scroll, boost::bind(&vertical_scrollbar::up_scroll_action, this)),
  down_scroll_button(m, this, point(0, sz.h() - sz.w()), dim(sz.w(), sz.w()), scroll_button::down_scroll,boost::bind(&vertical_scrollbar::down_scroll_action, this))
{}

void sge::gui::vertical_scrollbar::scroll_max(const size_type max)
{
	s_max = max; 
	scrollbar.height() = scroll_max_h()/(s_max+1);
	s_pos = std::min(s_pos,s_max);
	recalc_pos();
}

void sge::gui::vertical_scrollbar::up_scroll_action()
{
	if(s_pos > 0)
		--s_pos;
	recalc_pos();
}

void sge::gui::vertical_scrollbar::down_scroll_action()
{
	if(s_pos < s_max)
		++s_pos;
	recalc_pos();
}

void sge::gui::vertical_scrollbar::on_glob_mouse_move(const mouse_move_event& event)
{
	if(!scrollbar.pressed())
		return;

	const point p = event.pos();
	const unit distx = 0.1f;

	if(p.y() < 0 || p.y() > height() || 
	   p.x() < -distx || p.x() > width() + distx)
		return;

	scrollbar.y() = p.y();

	const unit miny = up_scroll_button.height();
	scrollbar.y() = std::max(scrollbar.y(),miny);

	const unit maxy = down_scroll_button.y() - scrollbar.height();
	scrollbar.y() = std::min(scrollbar.y(),maxy);

	s_pos = static_cast<size_type>((scrollbar.y() - miny) / (maxy-miny) * s_max);
}

void sge::gui::vertical_scrollbar::on_mouse_up(const mouse_button_event& event)
{
	if(event.code() == KC_MOUSEL)
		recalc_pos();
}

void sge::gui::vertical_scrollbar::on_mouse_press(const mouse_button_event& event)
{
	if(event.code() == KC_MOUSEL)
		move_scrollbar(event.pos());
}

void sge::gui::vertical_scrollbar::on_mouse_down(const mouse_button_event& event)
{
	if(event.code() == KC_MOUSEL)
		move_scrollbar(event.pos());
}

void sge::gui::vertical_scrollbar::move_scrollbar(const point click_pos)
{
	if(scrollbar.pressed())
		return;

	const size_type stride = 1;

	if(click_pos.y() > scrollbar.y() + scrollbar.height())
	{
		s_pos += stride;
		s_pos = std::min(s_pos,s_max);
	}
	else if(click_pos.y() < scrollbar.y())
	{
		if(s_pos >= stride)
			s_pos -= stride;
		else
			s_pos = 0;
	}
	recalc_pos();
}

void sge::gui::vertical_scrollbar::recalc_pos()
{
	scrollbar.y() = scroll_max_h()*(static_cast<unit>(s_pos)/(s_max+1)) + up_scroll_button.height();
}

sge::gui::unit sge::gui::vertical_scrollbar::scroll_max_h() const
{
	return height()-2*up_scroll_button.height();
}

sge::gui::vertical_scrollbar::size_type sge::gui::vertical_scrollbar::scroll_pos() const
{
	return s_pos;
}
