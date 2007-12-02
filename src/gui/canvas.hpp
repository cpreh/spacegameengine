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


#ifndef SGE_GUI_CANVAS_HPP_INCLUDED
#define SGE_GUI_CANVAS_HPP_INCLUDED

#include <string>

#include <boost/smart_ptr.hpp>

#include "../texture/manager.hpp"

#include "types.hpp"
#include "color.hpp"
#include "exception.hpp"
#include "mixing_policies.hpp"
#include "gradient_policies.hpp"

namespace sge {
namespace gui {

class canvas {
private:
	dim2 size_;
	boost::scoped_array<color> data;

public:
	canvas();
	canvas(const canvas &);
	canvas &operator=(const canvas &other);
	canvas(dim2 size_);
	canvas(dim2 size_, const color &fillcolor);

	void resize(const dim2 &newsize, bool keepcontent=false);
	inline const dim2 &size() const { return size_; }

	class invalid_coords : public exception {
	public:
		invalid_coords() : exception("Invalid coordinates.") {}
	};

	void pixel(const point &coords, const color &newcol);
	color &pixel(const point &coords);
	inline const color &pixel(const point &coords) const {
		return const_cast<canvas&>(*this).pixel(coords);
	}

	void blit(color::mixing_policy_t policy, const canvas &source, rect srccoord, point dest);
	template<typename MixingPolicy> inline void blit(const canvas &source, const rect &srccoord, const point &dest) {
		blit(MixingPolicy(), source, srccoord, dest);
	}
	void blit(color::mixing_policy_t policy, const canvas &source, rect srccoord, point dest, float alpha);
	template<typename MixingPolicy> inline void blit(const canvas &source, const rect &srccoord, const point &dest, float alpha) {
		blit(MixingPolicy(), source, srccoord, dest, alpha);
	}

	void fill_rect(rect area, const color &col);
	inline void fill(const color &col) { fill_rect(rect(point(0,0), size_), col); }

	void draw_line(color::mixing_policy_t policy, const point &from, const point &to, const color &col);
	template<typename MixingPolicy> inline void draw_line(const point &from, const point &to, const color &col) {
		draw_line(MixingPolicy(), from, to, col);
	}
	void draw_line(color::mixing_policy_t, color::gradient_policy_t, const point &from, const point &to, const color &colfrom, const color &colto);
	template<typename MixingPolicy, typename GradientPolicy> inline void draw_line(const point &from, const point &to, const color &colfrom, const color &colto) {
		draw_line(MixingPolicy(), GradientPolicy(), from, to, colfrom, colto);
	}

	void draw_arc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &col);
	template<typename MixingPolicy> inline void draw_arc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &col) {
		draw_arc(MixingPolicy(), boundary, arcfrom, arcto, col);
	}
	void draw_arc(color::mixing_policy_t, color::gradient_policy_t, const rect &boundary, float arcfrom, float arcto, const color &colfrom, const color &colto);
	template<typename MixingPolicy, typename GradientPolicy> inline void draw_arc(const rect &boundary, float arcfrom, float arcto, const color &colfrom, const color &colto) {
		draw_arc(MixingPolicy(), GradientPolicy(), boundary, arcfrom, arcto, colfrom, colto);
	}

	sge::virtual_texture_ptr to_texture(sge::texture_manager &texmgr, sge::virtual_texture_ptr texture = sge::virtual_texture_ptr()) const;

public: // static members
//	static canvas from_texture(const sge::texture &texture); // TODO
	static canvas from_image(const std::string &path);
};

}
}

#endif // SGE_GUI_CANVAS_HPP_INCLUDED
