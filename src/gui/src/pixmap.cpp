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

#include <cstring> // memcpy
#include "../pixmap.hpp"

namespace {

inline std::ptrdiff_t get_index_from_coords(const sge::gui::unit x, const sge::gui::unit y, const sge::gui::dim2 &sz) {
	return x + y*sz.w;
}

}

sge::gui::pixmap::pixmap() {}

sge::gui::pixmap::pixmap(const sge::gui::pixmap::pixmap &other)
: size_(other.size_), data(new sge::gui::color[size_.w * size_.h]) {
	std::memcpy(
		data.get(),
		other.data.get(),
		sizeof(sge::gui::color) * size_.w * size_.h
	);
}

sge::gui::pixmap::pixmap(sge::gui::dim2 size_)
: size_(size_), data(new sge::gui::color[size_.w * size_.h]) {}

sge::gui::pixmap::pixmap(sge::gui::dim2 size_, const sge::gui::color &fillcolor)
: size_(size_), data(new sge::gui::color[size_.w * size_.h]) {
	for (sge::gui::color *b=data.get(), *e=b+size_.w * size_.h; b != e; ++b) {
		*b = fillcolor;
	}
}

void sge::gui::pixmap::resize(const sge::gui::dim2 &newsize, bool keepcontent) {
	boost::scoped_array<sge::gui::color> temp(new sge::gui::color[newsize.w * newsize.h]);
	if (keepcontent) {
		sge::gui::dim2 tocopy;
			tocopy.w = (size_.w < newsize.w) ? size_.w : newsize.w;
			tocopy.h = (size_.h < newsize.h) ? size_.h : newsize.h;

		sge::gui::color
			*flineb = data.get(),
			*flinee = flineb + get_index_from_coords(0, tocopy.h, size_),
			*tline  = temp.get(),
			*fpixb, *fpixe, *tpix;
		for (; flineb != flinee; flineb += size_.w, tline += newsize.w)
			for (fpixb = flineb, fpixe = fpixb + tocopy.w, tpix = tline; fpixb != fpixe; ++fpixb, ++tpix)
				*tpix = *fpixb;
	}
	data.swap(temp);
}

void sge::gui::pixmap::pixel(const sge::gui::point &coords, const sge::gui::color &newcol) {
	pixel(coords) = newcol;
}

sge::gui::color &sge::gui::pixmap::pixel(const sge::gui::point &coords) {
	if (coords.x < 0 || coords.x >= size_.w ||
	    coords.y < 0 || coords.y >= size_.h) throw sge::gui::pixmap::invalid_coords();
	return data[get_index_from_coords(coords.x, coords.y, size_)];
}

void sge::gui::pixmap::blit(sge::gui::color::mixing_policy_t policy, const sge::gui::pixmap &source, sge::gui::rect srccoord, sge::gui::point dest) {
	if (srccoord.x >= source.size_.w || srccoord.y >= source.size_.h) return; // nothing to blit from
	if (dest.x >= size_.w || dest.y >= size_.h) return; // nowhere to blit to
	if (dest.x < 0) {srccoord.x -= dest.x; srccoord.w += dest.x; dest.x = 0; }
	if (dest.y < 0) { srccoord.y -= dest.y; srccoord.h += dest.y; dest.y = 0; }
	if (srccoord.x < 0) { dest.x -= srccoord.x; srccoord.w += srccoord.x; srccoord.x = 0; }
	if (srccoord.y < 0) { dest.y -= srccoord.y; srccoord.h += srccoord.y; srccoord.y = 0; }
	if (size_.w - dest.x < srccoord.w) srccoord.w = size_.w - dest.x;
	if (size_.h - dest.y < srccoord.h) srccoord.h = size_.h - dest.y;
	if (source.size_.w - srccoord.x < srccoord.w) srccoord.w = source.size_.w - srccoord.x;
	if (source.size_.h - srccoord.y < srccoord.h) srccoord.h = source.size_.h - srccoord.y;
	if (srccoord.w <= 0 || srccoord.h <= 0) return; // no data left to copy

	sge::gui::color // (_f_rom|_t_o) (_l_ine|_p_ixel) (_b_egin|_e_nd)
		*flb = source.data.get() + get_index_from_coords(srccoord.x, srccoord.y, source.size_),
		*fle = flb + srccoord.h * source.size_.w,
		*tlb = data.get() + get_index_from_coords(srccoord.x, srccoord.y, size_),
		*fpb, *fpe, *tpb;

	for (; flb != fle; flb += source.size_.w, tlb += size_.w)
		for (fpb = flb, fpe = fpb + srccoord.w, tpb = tlb; fpb != fpe; ++fpb, ++tpb)
			policy(*tpb, *fpb);
}

void sge::gui::pixmap::blit(color::mixing_policy_t policy, const pixmap &source, rect srccoord, point dest, float alpha) {
	if (srccoord.x >= source.size_.w || srccoord.y >= source.size_.h) return; // nothing to blit from
	if (dest.x >= size_.w || dest.y >= size_.h) return; // nowhere to blit to
	if (dest.x < 0) {srccoord.x -= dest.x; srccoord.w += dest.x; dest.x = 0; }
	if (dest.y < 0) { srccoord.y -= dest.y; srccoord.h += dest.y; dest.y = 0; }
	if (srccoord.x < 0) { dest.x -= srccoord.x; srccoord.w += srccoord.x; srccoord.x = 0; }
	if (srccoord.y < 0) { dest.y -= srccoord.y; srccoord.h += srccoord.y; srccoord.y = 0; }
	if (size_.w - dest.x < srccoord.w) srccoord.w = size_.w - dest.x;
	if (size_.h - dest.y < srccoord.h) srccoord.h = size_.h - dest.y;
	if (source.size_.w - srccoord.x < srccoord.w) srccoord.w = source.size_.w - srccoord.x;
	if (source.size_.h - srccoord.y < srccoord.h) srccoord.h = source.size_.h - srccoord.y;
	if (srccoord.w <= 0 || srccoord.h <= 0) return; // no data left to copy

	sge::gui::color // (_f_rom|_t_o) (_l_ine|_p_ixel) (_b_egin|_e_nd)
		*flb = source.data.get() + get_index_from_coords(srccoord.x, srccoord.y, source.size_),
		*fle = flb + srccoord.h * source.size_.w,
		*tlb = data.get() + get_index_from_coords(srccoord.x, srccoord.y, size_),
		*fpb, *fpe, *tpb;

	sge::gui::color current_pixel;
	for (; flb != fle; flb += source.size_.w, tlb += size_.w) {
		for (fpb = flb, fpe = fpb + srccoord.w, tpb = tlb; fpb != fpe; ++fpb, ++tpb) {
			current_pixel = *tpb;
			policy(current_pixel, *fpb);
			*tpb = sge::gui::gradient_policy::normal::mix(*tpb, current_pixel, alpha);
		}
	}
}

void sge::gui::pixmap::fill_rect(rect area, const color &col) {
	if (area.x < 0) { area.w += area.x; area.x = 0; }
	if (area.y < 0) { area.h += area.y; area.y = 0; }
	if (area.x + area.w > size_.w) area.w = size_.w - area.x;
	if (area.y + area.h > size_.h) area.h = size_.h - area.y;
	if (area.w <= 0 || area.h <= 0) return;

	sge::gui::color *lineb = data.get() + get_index_from_coords(area.x, area.y, size_),
	                *linee = lineb + area.h * size_.w,
	                *pixb, *pixe;
	for (; lineb != linee; lineb += size_.w)
		for (pixb = lineb, pixe = pixb + area.w; pixb != pixe; ++pixb)
			*pixb = col;
}

namespace {
	struct draw_line_coords {
		sge::gui::unit &largeunit, &smallunit;
		draw_line_coords(sge::gui::unit &lu, sge::gui::unit &su) : largeunit(lu), smallunit(su) {}
	};
}

void sge::gui::pixmap::draw_line(color::mixing_policy_t policy, const point &from, const point &to, const color &col) {
	if (to == from) {
		try {
			pixel(to).mix(policy, col);
		} catch(sge::gui::pixmap::invalid_coords &e) {}
		return;
	}

	sge::gui::unit
		delta_x = to.x - from.x,
		delta_y = to.y - from.y;

	sge::gui::point p(delta_x, delta_y);
	draw_line_coords coord = ((delta_x < 0) ? -delta_x : delta_x) < ((delta_y < 0) ? -delta_y : delta_y)
		? draw_line_coords(p.y, p.x)
		: draw_line_coords(p.x, p.y);
	const draw_line_coords size = ((delta_x < 0) ? -delta_x : delta_x) < ((delta_y < 0) ? -delta_y : delta_y)
		? draw_line_coords(size_.h, size_.w)
		: draw_line_coords(size_.w, size_.h);

	// Note: This code actually draws from to to from.
	// There is no reason for _this_ function to do so, but for the
	// version that uses a gradient for drawing, this will vastly ease
	// the gradient progess handling because it runs from 100% to 0%
	const sge::gui::unit
		largestep = (coord.largeunit < 0) ? 1 : -1;
	int
		numsteps = (coord.largeunit < 0) ? -coord.largeunit : coord.largeunit;
	const sge::gui::funit
		smallstep = -static_cast<sge::gui::funit>(coord.smallunit) / static_cast<sge::gui::funit>(numsteps);

	p.x = to.x; p.y = to.y;
	sge::gui::funit smallunit = coord.smallunit + 0.5;

	// sanitize primary direction
	if (coord.largeunit < 0) {
		if (largestep > 0) {
			numsteps -= -coord.largeunit;
			smallunit += -coord.largeunit * smallstep;
			coord.largeunit = 0;
		} else
			return; // no part of the line hits the rect
	} else if (coord.largeunit >= size.largeunit) {
		if (largestep < 0) {
			numsteps -= coord.largeunit - size.largeunit - 1;
			smallunit += (coord.largeunit - size.largeunit - 1) * smallstep;
			coord.largeunit = size.largeunit - 1;
		} else
			return; // no part of the line hits the rect
	}

	// sanitize secondary direction
	if (smallunit < 0) {
		if (smallstep > 0) {
			const int fullsteps = static_cast<sge::gui::unit>(-smallunit/smallstep);
			numsteps -= fullsteps;
			coord.largeunit += fullsteps;
			smallunit += fullsteps * smallstep;
		} else
			return; // no part of the line hits the rect
	} else if (smallunit > size.smallunit) {
		if (smallstep < 0) {
			const int fullsteps = static_cast<sge::gui::unit>(-smallunit/smallstep);
			numsteps -= fullsteps;
			coord.largeunit += fullsteps;
			smallunit += fullsteps * smallstep;
		} else
			return; // no part of the line hits the rect
	}

	bool prev_in_area = false, this_in_area;
	do {
		coord.smallunit = static_cast<sge::gui::unit>(smallunit);
		if (this_in_area = (p.x >= 0 && p.y >= 0 && p.x < size_.w && p.y < size_.h))
			pixel(p).mix(policy, col);

		else if (prev_in_area)
			// we've walked out of the rect - no chance to get back
			// into it on this line, so abort
			break;

		prev_in_area = this_in_area;
		coord.largeunit += largestep;
		smallunit += smallstep;
	} while (numsteps--);
}

//void sge::gui::pixmap::draw_line(color::mixing_policy_t policy, color::gradient_policy_t policy, const point &from, const point &to, const color &colfrom, const color &colto);
//void sge::gui::pixmap::draw_arc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &col);
//void sge::gui::pixmap::draw_arc(color::mixing_policy_t policy, color::gradient_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &colfrom, const color &colto);

sge::virtual_texture_ptr sge::gui::pixmap::to_texture(sge::texture_manager &texmgr, sge::virtual_texture_ptr texture) const {
	sge::gui::color *fromb = data.get(), *frome = fromb + (size_.w * size_.h);
	boost::scoped_array<sge::color> texdata(new sge::color[size_.w * size_.h]);
	sge::color *to = texdata.get();
	while (fromb != frome) {
		*to = fromb->rgba();
		++to; ++fromb;
	}

	if (texture &&
	    static_cast<sge::gui::unit>(texture->area().width()) == size_.w &&
	    static_cast<sge::gui::unit>(texture->area().height()) == size_.h) {
		texture->set_data(texdata.get());
		return texture;
	} else {
		return texmgr.add_texture(texdata.get(), size_.w, size_.h);
	}
}
