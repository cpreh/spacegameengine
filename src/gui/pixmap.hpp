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

#include "types.hpp"
#include "color.hpp"
#include "exception.hpp"
#include "mixing_policies.hpp"
#include "gradient_policies.hpp"

namespace sge {
namespace gui {

class pixmap {
public:
	pixmap();
	pixmap(const pixmap &);
	pixmap(unit width, unit height);
	~pixmap();

	void resize(const sge::gui::size &newsize, bool keepcontent=false);
	inline const sge::gui::size &size() const { return size_; }

	class invalid_coords : public runtime_error {
	public:
		invalid_coords() : runtime_error("Invalid coordinates.") {}
	}

	void pixel(const point &coords, const color &);
	color &pixel(const point &coords);
	inline const color &pixel(const point &coords) const {
		return const_cast<pixmap&>(*this).pixel(coords);
	}

	void blit(color::mixing_policy_t policy, const pixmap &source, const rect &srccoord, const point &dest);
	template<typename MixingPolicy = mixing_policy::normal> inline void blit(const pixmap &source, const rect &srccoord, const point &dest) {
		blit(&MixingPolicy::mixin, source, srccoord, dest);
	}
	void blit(color::mixing_policy_t policy, const pixmap &source, const rect &srccoord, const point &dest, float alpha);
	template<typename MixingPolicy = mixing_policy::normal> inline void blit(const pixmap &source, const rect &srccoord, const point &dest, float alpha) {
		blit(&MixingPolicy::mixin, source, srccoord, dest, alpha);
	}

	void fillRect(const rect &area, const color &col);
	inline void fill(const color &col) { fillRect(rect(point(0,0), size_), col); }

	void drawLine(color::mixing_policy_t policy, const point &from, const point &to, const color &col, bool antialiased=false);
	template<typename MixingPolicy = mixing_policy::normal> inline void drawLine(const point &from, const point &to, const color &col, bool antialiased=false)
		drawLine(&MixingPolicy::mixin, from, to, col, antialiased);
	}
	void drawLine(color::mixing_policy_t policy, color::gradient_policy_t policy, const point &from, const point &to, const color &colfrom, const color &colto, bool antialiased=false);
	template<typename MixingPolicy = mixing_policy::normal, typename GradientPolicy = gradient_policy::normal> inline void drawLine(const point &from, const point &to, const color &colfrom, const color &colto, bool antialiased=false)
		drawLine(&MixingPolicy::mixin, &GradientPolicy::mix, from, to, colfrom, colto, antialiased);
	}

	void drawArc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &col, bool antialiased=false);
	template<typename MixingPolicy = mixing_policy::normal> inline void drawArc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &col, bool antialiased=false)
		void drawArc(&MixingPolicy::mixin, const boundary, arcfrom, arcto, col, antialiased);
	}
	void drawArc(color::mixing_policy_t policy, color::gradient_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &colfrom, const color &colto, bool antialiased=false);
	template<typename MixingPolicy = mixing_policy::normal> inline void drawArc(color::mixing_policy_t policy, const rect &boundary, float arcfrom, float arcto, const color &colfrom, const color &colto, bool antialiased=false)
		void drawArc(&MixingPolicy::mixin, &GradientPolicy::mix, const boundary, arcfrom, arcto, colfrom, colto, antialiased);
	}

//	sge::texture toTexture() const;

private:
	sge::gui::size size_;
	boost::scoped_array<color> data;

public: // static members
//	static pixmap fromTexture(const sge::texture &texture); // TODO
//	static pixmap fromImage(const std::string &path); // TODO
};

}
}

#endif // SGE_GUI_PIXMAP_HPP_INCLUDED
