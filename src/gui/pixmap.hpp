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


#ifndef SGE_GUI_PIXMAP_HPP_INCLUDED
#define SGE_GUI_PIXMAP_HPP_INCLUDED

#include <string>

#include <boost/smart_ptr.hpp>

#include "../renderer/renderer.hpp"
#include "../renderer/texture.hpp"

#include "types.hpp"
#include "color.hpp"
#include "exception.hpp"
#include "mixing_policies.hpp"
#include "gradient_policies.hpp"

namespace sge {
namespace gui {

class pixmap {
private:
	dim2 size_;
	boost::scoped_array<color> data;

public:
	pixmap();
	pixmap(const pixmap &);
	pixmap(dim2 size_);
	pixmap(dim2 size_, const color &fillcolor);

	void resize(const dim2 &newsize, bool keepcontent=false);
	inline const dim2 &size() const { return size_; }

	class invalid_coords : public runtime_error {
	public:
		invalid_coords() : runtime_error("Invalid coordinates.") {}
	};

	void pixel(const point &coords, const color &newcol);
	color &pixel(const point &coords);
	inline const color &pixel(const point &coords) const {
		return const_cast<pixmap&>(*this).pixel(coords);
	}

	void blit(color::mixing_policy_t policy, const pixmap &source, rect srccoord, point dest);
	template<typename MixingPolicy> inline void blit(const pixmap &source, const rect &srccoord, const point &dest) {
		blit(&MixingPolicy::mixin, source, srccoord, dest);
	}
	void blit(color::mixing_policy_t policy, const pixmap &source, rect srccoord, point dest, float alpha);
	template<typename MixingPolicy> inline void blit(const pixmap &source, const rect &srccoord, const point &dest, float alpha) {
		blit(&MixingPolicy::mixin, source, srccoord, dest, alpha);
	}

	void fill_rect(rect area, const color &col);
	inline void fill(const color &col) { fill_rect(rect(point(0,0), size_), col); }

	void draw_line(color::mixing_policy_t policy, const point &from, const point &to, const color &col);
	template<typename MixingPolicy> inline void draw_line(const point &from, const point &to, const color &col) {
		draw_line(&MixingPolicy::mixin, from, to, col);
	}
	void draw_line(color::mixing_policy_t policy, color::gradient_policy_t policy, const point &from, const point &to, const color &colfrom, const color &colto);
	template<typename MixingPolicy, typename GradientPolicy> inline void draw_line(const point &from, const point &to, const color &colfrom, const color &colto) {
		draw_line(&MixingPolicy::mixin, &GradientPolicy::mix, from, to, colfrom, colto);
	}

	void draw_arc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &col);
	template<typename MixingPolicy> inline void draw_arc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &col) {
		draw_arc(&MixingPolicy::mixin, boundary, arcfrom, arcto, col);
	}
	void draw_arc(color::mixing_policy_t policy, color::gradient_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &colfrom, const color &colto);
	template<typename MixingPolicy, typename GradientPolicy> inline void draw_arc(const rect &boundary, float arcfrom, float arcto, const color &colfrom, const color &colto) {
		draw_arc(&MixingPolicy::mixin, &GradientPolicy::mix, boundary, arcfrom, arcto, colfrom, colto);
	}

	sge::texture_ptr to_texture(sge::renderer_ptr renderer, sge::texture_ptr texture = sge::texture_ptr()) const;

public: // static members
//	static pixmap from_texture(const sge::texture &texture); // TODO
//	static pixmap from_image(const std::string &path); // TODO
};

}
}

#endif // SGE_GUI_PIXMAP_HPP_INCLUDED
