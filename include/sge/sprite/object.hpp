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


#ifndef SGE_SPRITE_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_OBJECT_HPP_INCLUDED

#include "../export.hpp"
#include "../math/rect.hpp"
#include "../math/vector.hpp"
#include "../math/dim.hpp"
#include "../math/circle.hpp"
#include "../texture/virtual_texture.hpp"
#include "../renderer/color.hpp"
#include "types.hpp"
#include <boost/optional.hpp>

namespace sge
{
namespace sprite
{

extern const dim texture_dim;
extern const virtual_texture_ptr no_texture;

namespace defaults
{

extern const point pos_;
extern const virtual_texture_ptr texture_;
extern const dim dim_;
extern const color color_;
extern const depth_type depth_;
extern const rotation_type rotation_;
extern const bool visible_;

}

class object {
public:
	SGE_SYMBOL object(
		boost::optional<point> = defaults::pos_,
		boost::optional<virtual_texture_ptr> = defaults::texture_,
		boost::optional<dim> = defaults::dim_,
		boost::optional<color> = defaults::color_,
		boost::optional<depth_type> = defaults::depth_,
		boost::optional<rotation_type> = defaults::rotation_,
		boost::optional<bool> visible = defaults::visible_);

	SGE_SYMBOL unit& x();
	SGE_SYMBOL unit& y();
	SGE_SYMBOL point& pos();
	SGE_SYMBOL unit& w();
	SGE_SYMBOL unit& h();
	SGE_SYMBOL dim& size();
	SGE_SYMBOL depth_type& z();
	SGE_SYMBOL void visible(bool visible);
	SGE_SYMBOL void set_texture(virtual_texture_ptr);
	SGE_SYMBOL void rotation(rotation_type rot);
	SGE_SYMBOL void rotate_around(point p);
	SGE_SYMBOL void rotate_around();
	SGE_SYMBOL void repeat(repetition_type);
	SGE_SYMBOL void set_color(color c);
	SGE_SYMBOL void set_center(const point &);
	
	SGE_SYMBOL const unit& x() const;
	SGE_SYMBOL const unit& y() const;
	SGE_SYMBOL const depth_type& z() const;
	SGE_SYMBOL const point& pos() const;
	SGE_SYMBOL const unit& w() const;
	SGE_SYMBOL const unit& h() const;
	SGE_SYMBOL const dim& size() const;
	SGE_SYMBOL bool visible() const;
	SGE_SYMBOL rect get_rect() const;
	SGE_SYMBOL point center() const;
	SGE_SYMBOL rotation_type rotation() const;
	SGE_SYMBOL space_unit radius() const;
	SGE_SYMBOL repetition_type repeat() const;
	SGE_SYMBOL color get_color() const;
	SGE_SYMBOL rect bounding_quad() const;
	SGE_SYMBOL math::circle bounding_circle() const;
	SGE_SYMBOL const point rotation_center() const;
	SGE_SYMBOL const virtual_texture_ptr get_texture() const;
private:
	SGE_SYMBOL static bool equal(const object& l, const object& r);
	SGE_SYMBOL static bool less(const object& l, const object& r);

	friend class system;

	point               pos_;
	dim                 size_;
	depth_type          z_;
	rotation_type       rotation_;
	virtual_texture_ptr tex;
	point               rot_around_;
	repetition_type     repeat_;
	color               color_;
	bool                visible_;
	bool                use_rot_around;
};

}
}

#endif
