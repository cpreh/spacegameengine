/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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

#include "../defaultskin.hpp"

#include <boost/weak_ptr.hpp>

#include "../canvas.hpp"
#include "../color.hpp"
#include "../widget.hpp"

namespace {
	boost::weak_ptr<sge::gui::skin> defaultskin_instance;

	inline sge::gui::rect border_rect(
		const sge::gui::rect &rct,
		const sge::gui::unit t,
		const sge::gui::unit r,
		const sge::gui::unit b,
		const sge::gui::unit l
	) { return sge::gui::rect(rct.x-r, rct.y-t, rct.w+r+l, rct.h+t+b); }
	inline sge::gui::rect border_rect(
		const sge::gui::rect &rct,
		const sge::gui::unit v,
		const sge::gui::unit h
	) { return border_rect(rct, v, h, v, h); }
	inline sge::gui::rect border_rect(
		const sge::gui::rect &rct,
		const sge::gui::unit uni
	) { return border_rect(rct, uni, uni, uni, uni); }
}

sge::gui::defaultskin::defaultskin() {}
sge::gui::defaultskin::~defaultskin() {}

sge::gui::rect sge::gui::defaultskin::adjust_to_border(widget*, border_style::type bt, rect r) const {
	switch (bt) {
		case skin::border_style::frame:
		case skin::border_style::button:
		case skin::border_style::iconbutton:
			return border_rect(r, 4);

		default:
			return r;
	}
}

void sge::gui::defaultskin::draw_border(widget*, border_style::type bt, focus_modifier::type ft, rect r, canvas &dest) const {
	color lg(255, 255, 255, 176),
	      ds(  0,   0,   0, 176),
	      ls(  0,   0,   0,  97);

	point x(1,0), y(0,1), x_(r.w-1,0), y_(0,r.h-1), p(r.position());

	mixing_policy::normal mix;
	switch (bt) {
		case border_style::none:
			return;

		case border_style::button:
		case border_style::iconbutton:
			if (ft == focus_modifier::active || ft == focus_modifier::hover_active) {
				// top
				dest.draw_line(mix, p, p+x_-x, ds);
				dest.draw_line(mix, p+y+x, p+y+x_-x-x, ls);
				// left
				dest.draw_line(mix, p, p+y_-y, ds);
				dest.draw_line(mix, p+x+y, p+x+y_-y-y, ls);
				// bottom
//				dest.draw_line(mix, p+y_, p+x_+y_, ds);
				dest.draw_line(mix, p+y_-y+x, p+x_-x+y_-y, lg);
				// right
//				dest.draw_line(mix, p+x_, p+x_+y_-y, ds);
				dest.draw_line(mix, p+x_-x+y, p+x_-x+y_-y-y, lg);
				return;
			}
		default:
			// top
//			dest.draw_line(mix, p, p+x_-x, ds);
			dest.draw_line(mix, p+y+x, p+y+x_-x-x, lg);
			// left
//			dest.draw_line(mix, p, p+y_-y, ds);
			dest.draw_line(mix, p+x+y, p+x+y_-y-y, lg);
			// bottom
			dest.draw_line(mix, p+y_, p+x_+y_, ds);
			dest.draw_line(mix, p+y_-y+x, p+x_-x+y_-y, ls);
			// right
			dest.draw_line(mix, p+x_, p+x_+y_-y, ds);
			dest.draw_line(mix, p+x_-x+y, p+x_-x+y_-y-y, ls);
			return;
	}
}

void sge::gui::defaultskin::draw_background(widget *w, border_style::type, focus_modifier::type fm, rect r, canvas &dest) const {
	color c = w->background_color()
		? *(w->background_color())
		: color(192, 192, 192, 255);

	if (fm == focus_modifier::hover || fm == focus_modifier::hover_active)
		c.mix<mixing_policy::normal>(color(255,255,255,64)); // brighten 25%

	dest.fill_rect(r, c);
}

void sge::gui::defaultskin::draw_icon(widget *w, stock_icon::type it, focus_modifier::type, rect r, canvas &dest) const {
	color c = w->foreground_color()
		? *(w->foreground_color())
		: color(0, 0, 0, 255);

	point o = point(icon_size().w, icon_size().h),
	      p = r.position() + ((point(r.w-1, r.h-1) - o) / 2),
	      i;
	o += p;

	const unsigned *rp = icons[it];
	for (i.y = p.y; i.y < o.y; ++i.y) {
		unsigned row = *(rp++);
		for (i.x = p.x; i.x < o.x; ++i.x) {
			if (row & 1)
				dest.pixel(i).mix<mixing_policy::normal>(c);
			row >>= 1;
		}
	}
}

sge::gui::skin_ptr sge::gui::defaultskin::get() {
	skin_ptr sp = defaultskin_instance.lock();
	if (!sp) {
		sp.reset(new defaultskin());
		defaultskin_instance = sp;
	}
	return sp;
}
