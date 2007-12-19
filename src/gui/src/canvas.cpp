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


#include <cmath> // memcpy
#include <cstring> // memcpy
#include "../../math/constants.hpp"
#include "../../math/rect_impl.hpp"
#include "../canvas.hpp"

namespace {

inline std::ptrdiff_t get_index_from_coords(const sge::gui::unit x, const sge::gui::unit y, const sge::gui::dim2 &sz) {
	return x + y*sz.w;
}

inline sge::gui::funit cosine(sge::gui::funit x) {
	return std::cos(x * 2 * sge::math::PI);
}

inline sge::gui::funit sine(sge::gui::funit x) {
	return cosine(x - 0.25);
}

}

sge::gui::canvas::canvas() {}

sge::gui::canvas::canvas(const sge::gui::canvas::canvas &other)
: size_(other.size_), data(new sge::gui::color[size_.w * size_.h]) {
	std::memcpy(
		data.get(),
		other.data.get(),
		sizeof(sge::gui::color) * size_.w * size_.h
	);
}

sge::gui::canvas::canvas &sge::gui::canvas::operator=(const sge::gui::canvas::canvas &other) {
	if (size_ != other.size_) {
		size_ = other.size_;
		boost::scoped_array<sge::gui::color> dt(new sge::gui::color[size_.w * size_.h]);
		data.swap(dt);
	}
	std::memcpy(
		data.get(),
		other.data.get(),
		sizeof(sge::gui::color) * size_.w * size_.h
	);
	return *this;
}

sge::gui::canvas::canvas(sge::gui::dim2 size_)
: size_(size_), data(new sge::gui::color[size_.w * size_.h]) {}

sge::gui::canvas::canvas(sge::gui::dim2 size_, const sge::gui::color &fillcolor)
: size_(size_), data(new sge::gui::color[size_.w * size_.h]) {
	for (sge::gui::color *b=data.get(), *e=b+size_.w * size_.h; b != e; ++b) {
		*b = fillcolor;
	}
}

void sge::gui::canvas::resize(const sge::gui::dim2 &newsize, bool keepcontent) {
	if (newsize == size_) return;
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
	size_ = newsize;
	data.swap(temp);
}

void sge::gui::canvas::pixel(const sge::gui::point &coords, const sge::gui::color &newcol) {
	pixel(coords) = newcol;
}

sge::gui::color &sge::gui::canvas::pixel(const sge::gui::point &coords) {
	if (coords.x < 0 || coords.x >= size_.w ||
	    coords.y < 0 || coords.y >= size_.h) throw sge::gui::canvas::invalid_coords();
	return data[get_index_from_coords(coords.x, coords.y, size_)];
}

void sge::gui::canvas::blit(sge::gui::color::mixing_policy_t policy, const sge::gui::canvas &source, sge::gui::rect srccoord, sge::gui::point dest) {
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
		*tlb = data.get() + get_index_from_coords(dest.x, dest.y, size_),
		*fpb, *fpe, *tpb;

	for (; flb != fle; flb += source.size_.w, tlb += size_.w)
		for (fpb = flb, fpe = fpb + srccoord.w, tpb = tlb; fpb != fpe; ++fpb, ++tpb)
			policy(*tpb, *fpb);
}

void sge::gui::canvas::blit(color::mixing_policy_t policy, const canvas &source, rect srccoord, point dest, float alpha) {
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
		*tlb = data.get() + get_index_from_coords(dest.x, dest.y, size_),
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

void sge::gui::canvas::fill_rect(rect area, const color &col) {
	if (area.x < 0) { area.w += area.x; area.x = 0; }
	if (area.y < 0) { area.h += area.y; area.y = 0; }
	if (area.x + area.w > size_.w) area.w = size_.w - area.x;
	if (area.y + area.h > size_.h) area.h = size_.h - area.y;
	if (area.w <= 0 || area.h <= 0) return;

	sge::gui::color *lineb = data.get() + get_index_from_coords(area.x, area.y, size_),
	                *linee = lineb + area.h * size_.w,
	                *pixb, *pixe;
	for (int i=0, j; lineb != linee; lineb += size_.w, ++i)
		for (j=0, pixb = lineb, pixe = pixb + area.w; pixb != pixe; ++pixb, ++j)
			*pixb = col;
}

namespace {
	struct draw_line_coords {
		sge::gui::unit &largeunit, &smallunit;
		draw_line_coords(sge::gui::unit &lu, sge::gui::unit &su) : largeunit(lu), smallunit(su) {}
	};
}

void sge::gui::canvas::draw_line(color::mixing_policy_t policy, const point &from, const point &to, const color &col) {
	if (to == from) {
		try {
			pixel(to).mix(policy, col);
		} catch(sge::gui::canvas::invalid_coords &e) {}
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
			coord.largeunit += fullsteps * largestep;
			smallunit += fullsteps * smallstep;
		} else
			return; // no part of the line hits the rect
	} else if (smallunit > size.smallunit) {
		if (smallstep < 0) {
			const int fullsteps = static_cast<sge::gui::unit>((size.smallunit - smallunit)/smallstep);
			numsteps -= fullsteps;
			coord.largeunit += fullsteps * largestep;
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

void sge::gui::canvas::draw_line(color::mixing_policy_t policy, color::gradient_policy_t gpolicy, const point &from, const point &to, const color &colfrom, const color &colto) {
	if (to == from) {
		try {
			pixel(to).mix(policy, gpolicy(colfrom, colto, 0));
		} catch(sge::gui::canvas::invalid_coords &e) {}
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
		smallstep = -static_cast<sge::gui::funit>(coord.smallunit) / static_cast<sge::gui::funit>(numsteps),
		gradientstep = 1.0 / numsteps;

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
			coord.largeunit += fullsteps * largestep;
			smallunit += fullsteps * smallstep;
		} else
			return; // no part of the line hits the rect
	} else if (smallunit > size.smallunit) {
		if (smallstep < 0) {
			const int fullsteps = static_cast<sge::gui::unit>((size.smallunit - smallunit)/smallstep);
			numsteps -= fullsteps;
			coord.largeunit += fullsteps * largestep;
			smallunit += fullsteps * smallstep;
		} else
			return; // no part of the line hits the rect
	}

	bool prev_in_area = false, this_in_area;
	sge::gui::funit gradientposition = numsteps * gradientstep;
	do {
		coord.smallunit = static_cast<sge::gui::unit>(smallunit);
		if (this_in_area = (p.x >= 0 && p.y >= 0 && p.x < size_.w && p.y < size_.h))
			pixel(p).mix(policy, gpolicy(colfrom, colto, gradientposition));

		else if (prev_in_area)
			// we've walked out of the rect - no chance to get back
			// into it on this line, so abort
			break;

		prev_in_area = this_in_area;
		coord.largeunit += largestep;
		smallunit += smallstep;
		gradientposition -= gradientstep;
	} while (numsteps--);
}

void sge::gui::canvas::draw_arc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &col) {
	arcfrom /= 2 * sge::math::PI; arcto /= 2 * sge::math::PI;
	double stupid_cstdlib_modf_urgently_needs_this_dummy;

	sge::gui::fpoint excenter;
	sge::gui::fdim2  dimension(boundary.w-1, boundary.h-1);
	{ sge::gui::funit
		exx = (dimension.w < 0) ? -dimension.w : dimension.w,
		exy = (dimension.h < 0) ? -dimension.h : dimension.h;
		if (exx > exy) {
			excenter.x = 1.0;
			excenter.y = exy/exx;
		} else {
			excenter.x = exx/exy;
			excenter.y = 1.0;
		}
	}
	dimension.w *= 0.5;
	dimension.h *= 0.5;
	const sge::gui::fpoint center(
		boundary.x + dimension.w + 0.5,
		boundary.y + dimension.h + 0.5
	); // rounding for int cast ---^^^


	const sge::gui::funit
		stepmultiplyer = (arcto < arcfrom) ? -1 : 1,
		basestep = stepmultiplyer * excenter.x * excenter.y * (0.5 / sge::math::PI) / ((dimension.w < dimension.h) ? dimension.w : dimension.h);

	sge::gui::unit numstepsleft = 0;
	{ sge::gui::funit arc = arcfrom; sge::gui::funit refined_arc;
		while (stepmultiplyer * arc <= stepmultiplyer * arcto) {
			++numstepsleft;
			refined_arc = 2 * std::modf(arc, &stupid_cstdlib_modf_urgently_needs_this_dummy); // -2 .. 2
			// fold full circle (circumference = 4)
			// to first quarter of a circle
			if (refined_arc < 0.0) refined_arc = 2.0 + refined_arc;
			if (refined_arc > 1.0) refined_arc = 2.0 - refined_arc;
			arc += basestep * (refined_arc * excenter.y + (1.0 - refined_arc) * excenter.x);
		}
	}
	const sge::gui::unit numsteps = numstepsleft;
	if (!numsteps) return;

	const sge::gui::point startpoint(
		static_cast<sge::gui::unit>(center.x + dimension.w * cosine(arcfrom)),
		static_cast<sge::gui::unit>(center.y - dimension.h * sine(arcfrom))
	);

	--numstepsleft;
	try {
		pixel(startpoint).mix(policy, col);
	} catch (...) {}

	sge::gui::point thispoint, lastpoint = startpoint;
	sge::gui::funit arc = arcfrom, refined_arc;
	while(numstepsleft--) {
		refined_arc = 2 * std::modf(arc, &stupid_cstdlib_modf_urgently_needs_this_dummy); // -2 .. 2
		// fold full circle (circumference = 4)
		// to first quarter of a circle
		if (refined_arc < 0.0) refined_arc = 2.0 + refined_arc;
		if (refined_arc > 1.0) refined_arc = 2.0 - refined_arc;
		arc += basestep * (refined_arc * excenter.y + (1.0 - refined_arc) * excenter.x);

		thispoint.x = static_cast<sge::gui::unit>(center.x + dimension.w * cosine(arc));
		thispoint.y = static_cast<sge::gui::unit>(center.y - dimension.h * sine(arc));

		if (thispoint != lastpoint && (numstepsleft || (thispoint != startpoint))) try {
			pixel(thispoint).mix(policy, col);
		} catch(...) {}

		lastpoint = thispoint;
	}
}

void sge::gui::canvas::draw_arc(color::mixing_policy_t policy, color::gradient_policy_t gradientpolicy, const rect &boundary, float arcfrom, float arcto, const color &colfrom, const color &colto) {
	arcfrom /= 2 * sge::math::PI; arcto /= 2 * sge::math::PI;
	double stupid_cstdlib_modf_urgently_needs_this_dummy;

	sge::gui::fpoint excenter;
	sge::gui::fdim2  dimension(boundary.w-1, boundary.h-1);
	{ sge::gui::funit
		exx = (dimension.w < 0) ? -dimension.w : dimension.w,
		exy = (dimension.h < 0) ? -dimension.h : dimension.h;
		if (exx > exy) {
			excenter.x = 1.0;
			excenter.y = exy/exx;
		} else {
			excenter.x = exx/exy;
			excenter.y = 1.0;
		}
	}
	dimension.w *= 0.5;
	dimension.h *= 0.5;
	const sge::gui::fpoint center(
		boundary.x + dimension.w + 0.5,
		boundary.y + dimension.h + 0.5
	); // rounding for int cast ---^^^


	const sge::gui::funit
		stepmultiplyer = (arcto < arcfrom) ? -1 : 1,
		basestep = stepmultiplyer * excenter.x * excenter.y * (0.5 / sge::math::PI) / ((dimension.w < dimension.h) ? dimension.w : dimension.h);

	sge::gui::unit numstepsleft = 0;
	{ sge::gui::funit arc = arcfrom; sge::gui::funit refined_arc;
		while (stepmultiplyer * arc <= stepmultiplyer * arcto) {
			++numstepsleft;
			refined_arc = 2 * std::modf(arc, &stupid_cstdlib_modf_urgently_needs_this_dummy); // -2 .. 2
			// fold full circle (circumference = 4)
			// to first quarter of a circle
			if (refined_arc < 0.0) refined_arc = 2.0 + refined_arc;
			if (refined_arc > 1.0) refined_arc = 2.0 - refined_arc;
			arc += basestep * (refined_arc * excenter.y + (1.0 - refined_arc) * excenter.x);
		}
	}
	if (!numstepsleft) return;
	const sge::gui::unit numsteps = numstepsleft;
	const sge::gui::funit gradientstep = (numsteps > 1) ? 1.0 / (numsteps - 1) : 0;

	const sge::gui::point startpoint(
		static_cast<sge::gui::unit>(center.x + dimension.w * cosine(arcfrom)),
		static_cast<sge::gui::unit>(center.y - dimension.h * sine(arcfrom))
	);


	--numstepsleft;
	try {
		pixel(startpoint).mix(policy, gradientpolicy(colfrom, colto, 0));
	} catch (...) {}

	sge::gui::point thispoint, lastpoint = startpoint;
	sge::gui::funit arc = arcfrom, refined_arc, gradient = gradientstep;
	while(numstepsleft--) {
		refined_arc = 2 * std::modf(arc, &stupid_cstdlib_modf_urgently_needs_this_dummy); // -2 .. 2
		// fold full circle (circumference = 4)
		// to first quarter of a circle
		if (refined_arc < 0.0) refined_arc = 2.0 + refined_arc;
		if (refined_arc > 1.0) refined_arc = 2.0 - refined_arc;
		arc += basestep * (refined_arc * excenter.y + (1.0 - refined_arc) * excenter.x);

		thispoint.x = static_cast<sge::gui::unit>(center.x + dimension.w * cosine(arc));
		thispoint.y = static_cast<sge::gui::unit>(center.y - dimension.h * sine(arc));

		if (thispoint != lastpoint && (numstepsleft || (thispoint != startpoint))) try {
			pixel(thispoint).mix(policy, gradientpolicy(colfrom, colto, gradient));
		} catch(...) {}

		lastpoint = thispoint;
		gradient += gradientstep;
	}
}

sge::virtual_texture_ptr sge::gui::canvas::to_texture(sge::texture_manager &texmgr, sge::virtual_texture_ptr texture) const {
	sge::gui::color *fromb = data.get(), *frome = fromb + (size_.w * size_.h);
	boost::scoped_array<sge::color> texdata(new sge::color[size_.w * size_.h]);
	sge::color *to = texdata.get();
	while (fromb != frome) {
		*to = *fromb;
		++to; ++fromb;
	}

	if (texture &&
	    static_cast<sge::gui::unit>(texture->area().w()) == size_.w &&
	    static_cast<sge::gui::unit>(texture->area().h()) == size_.h) {
		texture->set_data(texdata.get());
		return texture;
	} else {
		return texmgr.add_texture(texdata.get(), texture::dim_type(size_.w, size_.h));
	}
}
