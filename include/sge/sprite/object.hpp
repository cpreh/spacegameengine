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
#include "../texture/part.hpp"
#include "../renderer/color.hpp"
#include "types.hpp"
#include <boost/optional.hpp>

namespace sge
{
namespace sprite
{

SGE_SYMBOL extern const dim texture_dim;
SGE_SYMBOL extern const texture::part_ptr no_texture;

namespace defaults
{

SGE_SYMBOL extern const point pos_;
SGE_SYMBOL extern const texture::part_ptr texture_;
SGE_SYMBOL extern const dim dim_;
SGE_SYMBOL extern const color color_;
SGE_SYMBOL extern const depth_type depth_;
SGE_SYMBOL extern const rotation_type rotation_;
SGE_SYMBOL extern const bool visible_;

}

class object {
public:
	SGE_SYMBOL object(
		boost::optional<point> = defaults::pos_,
		boost::optional<texture::part_ptr> = defaults::texture_,
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
	SGE_SYMBOL void set_texture(texture::part_ptr);
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
	SGE_SYMBOL const texture::part_ptr get_texture() const;
private:
	point               pos_;
	dim                 size_;
	depth_type          z_;
	rotation_type       rotation_;
	texture::part_ptr   tex;
	point               rot_around_;
	repetition_type     repeat_;
	color               color_;
	bool                visible_;
	bool                use_rot_around;
};

}
}

#endif
