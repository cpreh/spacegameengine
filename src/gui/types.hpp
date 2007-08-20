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
typedef float funit;

struct rect;
struct point {
	unit x, y;
	point() : x(0), y(0) {}
	point(const unit x, const unit y) : x(x), y(y) {}
	inline bool operator==(const point &other) const { return x == other.x && y == other.y; }
	inline bool operator!=(const point &other) const { return !operator==(other); }
	inline point &operator+=(const point &other) { x+=other.x; y+=other.y; return *this; }
	inline point operator+(const point &other) const { point t=*this; return t+=other; }
	inline point operator-() const { return point(-x, -y); }
	inline point &operator-=(const point &other) { return (*this)+=-other; }
	inline point operator-(const point &other) const { point t=*this; return t-=other; }
	point normalize(const rect &area) const;
	inline bool within(const rect &area) const { return operator==(normalize(area)); }
};

struct dim2 {
	unit w, h;
	dim2() : w(0), h(0) {}
	dim2(const unit w, const unit h) : w(w), h(h) {}
	inline bool operator==(const dim2 &other) const { return w == other.w && h == other.h; }
	inline bool operator!=(const dim2 &other) const { return !operator==(other); }
};

struct rect {
	unit x, y, w, h;
	rect() : x(0), y(0), w(0), h(0) {}
	rect(const unit x, const unit y, const unit w, const unit h) : x(x), y(y), w(w), h(h) {}
	rect(const point &p, const dim2 &s) : x(p.x), y(p.y), w(s.w), h(s.h) {}

	inline void position(const point &p) { x=p.x; y=p.y; }
	inline point position() const { return point(x, y); }
	inline void size(const dim2 &s) { w=s.w; h=s.h; }
	inline dim2 size() const { return dim2(w, h); }

	inline bool operator==(const rect &other) const { return x == other.x && y == other.y && w == other.w && h == other.h; }
	inline bool operator!=(const rect &other) const { return !operator==(other); }
};

struct frect;
struct fpoint {
	funit x, y;
	fpoint() : x(0), y(0) {}
	fpoint(const funit x, const funit y) : x(x), y(y) {}
	inline bool operator==(const fpoint &other) const { return x == other.x && y == other.y; }
	inline bool operator!=(const fpoint &other) const { return !operator==(other); }
	inline fpoint &operator+=(const fpoint &other) { x+=other.x; y+=other.y; return *this; }
	inline fpoint operator+(const fpoint &other) const { fpoint t=*this; return t+=other; }
	inline fpoint operator-() const { return fpoint(-x, -y); }
	inline fpoint &operator-=(const fpoint &other) { return (*this)+=-other; }
	inline fpoint operator-(const fpoint &other) const { fpoint t=*this; return t-=other; }
	fpoint normalize(const frect &area) const;
	inline bool within(const frect &area) const { return operator==(normalize(area)); }
};

struct fdim2 {
	funit w, h;
	fdim2() : w(0), h(0) {}
	fdim2(const funit w, const funit h) : w(w), h(h) {}
	inline bool operator==(const fdim2 &other) const { return w == other.w && h == other.h; }
	inline bool operator!=(const fdim2 &other) const { return !operator==(other); }
};

struct frect {
	funit x, y, w, h;
	frect() : x(0), y(0), w(0), h(0) {}
	frect(const funit x, const funit y, const funit w, const funit h) : x(x), y(y), w(w), h(h) {}
	frect(const fpoint &p, const fdim2 &s) : x(p.x), y(p.y), w(s.w), h(s.h) {}

	inline void position(const fpoint &p) { x=p.x; y=p.y; }
	inline fpoint position() const { return fpoint(x, y); }
	inline void size(const fdim2 &s) { w=s.w; h=s.h; }
	inline fdim2 size() const { return fdim2(w, h); }

	inline bool operator==(const frect &other) const { return x == other.x && y == other.y && w == other.w && h == other.h; }
	inline bool operator!=(const frect &other) const { return !operator==(other); }
};

}
}

#endif // SGE_GUI_TYPES_HPP_INCLUDED
