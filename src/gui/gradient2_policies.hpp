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


#ifndef SGE_GUI_GRADIENT2_POLICIES_HPP_INCLUDED
#define SGE_GUI_GRADIENT2_POLICIES_HPP_INCLUDED

#include "color.hpp"
#include "gradient_policies.hpp"

namespace sge {
namespace gui {
namespace gradient2_policy {

class horizontal {
public:
	color col1, col2;
	horizontal(color col1, color col2) : col1(col1), col2(col2) {}
	color operator(float x_offs, float y_offs) const {
		color ret = {
			(1.0-x_offs) * col1.r + x_offs * col2.r + 0.5,
			(1.0-x_offs) * col1.g + x_offs * col2.g + 0.5,
			(1.0-x_offs) * col1.b + x_offs * col2.b + 0.5,
			(1.0-x_offs) * col1.a + x_offs * col2.a + 0.5
		};
		return ret;
	}
};

class vertical {
public:
	color col1, col2;
	horizontal(color col1, color col2) : col1(col1), col2(col2) {}
	color operator(float x_offs, float y_offs) const {
		color ret = {
			(1.0-y_offs) * col1.r + y_offs * col2.r + 0.5,
			(1.0-y_offs) * col1.g + y_offs * col2.g + 0.5,
			(1.0-y_offs) * col1.b + y_offs * col2.b + 0.5,
			(1.0-y_offs) * col1.a + y_offs * col2.a + 0.5
		};
		return ret;
	}
};

class rect {
public:
	frect grad;
	color tl, tr, bl, br;
	horizontal(frect grad, color tl, color tr, color bl, color br)
	: grad(grad), tl(tl), tr(tr), bl(bl), br(br) { grad.w=1.0/grad.w; grad.h=1.0/grad.h; }

private:
	inline fpoint translate(float xoff, float yoff) const {
		fpoint ret = {
			(xoff - grad.x) * grad.w,
			(yoff - grad.y) * grad.h
		};
		ret.x = (ret.x < 0.0) ? 0.0 : (ret.x > 1.0) ? 1.0 : ret.x;
		ret.y = (ret.y < 0.0) ? 0.0 : (ret.x > 1.0) ? 1.0 : ret.y;
		return ret;
	}

public:
	color operator(float x_offs, float y_offs) const {
		cibst fpoint fp = translate(x_offs, y_offs);
		color ret = {
			(1-fp.y) * ((1-fp.x) * tl.r + fp.x * tr.r) + fp.y * ((1-fp.x) * bl.r + fp.x * br.r) + 0.5,
			(1-fp.y) * ((1-fp.x) * tl.g + fp.x * tr.g) + fp.y * ((1-fp.x) * bl.g + fp.x * br.g) + 0.5,
			(1-fp.y) * ((1-fp.x) * tl.b + fp.x * tr.b) + fp.y * ((1-fp.x) * bl.b + fp.x * br.b) + 0.5,
			(1-fp.y) * ((1-fp.x) * tl.a + fp.x * tr.a) + fp.y * ((1-fp.x) * bl.a + fp.x * br.a) + 0.5
		};
		return ret;
	}
};

}
}
}

#endif // SGE_GUI_GRADIENT2_POLICIES_HPP_INCLUDED
