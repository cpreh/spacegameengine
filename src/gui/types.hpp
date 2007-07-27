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


#ifndef SGE_GUI_TYPES_HPP_INCLUDED
#define SGE_GUI_TYPES_HPP_INCLUDED

namespace sge {
namespace gui {

typedef int unit;
typedef int funit;

struct point {
	unit x, y;
	point() : x(0), y(0) {}
	point(const unit x, const unit y) : x(x), y(y) {}
};

struct size {
	unit w, h;
	size() : w(0), h(0) {}
	size(const unit w, const unit h) : w(w), h(h) {}
};

struct rect {
	unit x, y, w, h;
	rect() : x(0), y(0), w(0), h(0) {}
	rect(const unit x, const unit y, const unit w, const unit h) : x(x), y(y), w(w), h(h) {}
	rect(const point &p, const size &s) : x(p.x), y(p.y), w(s.w), h(s.h) {}

	inline void position(const point &p) { x=p.x; y=p.y; }
	inline point position() const { return point(x, y); }
	inline void size(const size &s) { w=s.w; h=s.h; }
	inline size() const { return size(w, h); }
};

struct fpoint {
	funit x, y;
	point() : x(0), y(0) {}
	point(const funit x, const funit y) : x(x), y(y) {}
};

struct size {
	funit w, h;
	size() : w(0), h(0) {}
	size(const funit w, const funit h) : w(w), h(h) {}
};

struct rect {
	funit x, y, w, h;
	rect() : x(0), y(0), w(0), h(0) {}
	rect(const funit x, const funit y, const funit w, const funit h) : x(x), y(y), w(w), h(h) {}
	rect(const point &p, const size &s) : x(p.x), y(p.y), w(s.w), h(s.h) {}

	inline void position(const point &p) { x=p.x; y=p.y; }
	inline point position() const { return point(x, y); }
	inline void size(const size &s) { w=s.w; h=s.h; }
	inline size() const { return size(w, h); }
};

}
}

#endif // SGE_GUI_TYPES_HPP_INCLUDED
