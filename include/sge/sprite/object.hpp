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

#include "types.hpp"
#include "../export.hpp"
#include "../texture/part_fwd.hpp"
#include <boost/optional.hpp>

namespace sge
{
namespace sprite
{

SGE_SYMBOL extern const dim texture_dim;
SGE_SYMBOL extern const texture::const_part_ptr no_texture;

namespace defaults
{

SGE_SYMBOL extern point const pos_;
SGE_SYMBOL extern texture::const_part_ptr const texture_;
SGE_SYMBOL extern const dim dim_;
SGE_SYMBOL extern const color color_;
SGE_SYMBOL extern const depth_type depth_;
SGE_SYMBOL extern const rotation_type rotation_;
SGE_SYMBOL extern const bool visible_;

}

class object {
public:
	typedef sprite::rect rect_t;
	typedef sprite::color color_t;

	SGE_SYMBOL object(
		boost::optional<point> = defaults::pos_,
		boost::optional<texture::const_part_ptr> = defaults::texture_,
		boost::optional<dim> = defaults::dim_,
		boost::optional<color_t> = defaults::color_,
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
	SGE_SYMBOL void texture(texture::const_part_ptr);
	SGE_SYMBOL void rotation(rotation_type rot);
	SGE_SYMBOL void rotate_around(point p);
	SGE_SYMBOL void rotate_around();
	SGE_SYMBOL void repeat(repetition_type);
	SGE_SYMBOL void color(color_t c);
	SGE_SYMBOL void center(point const &);
	
	SGE_SYMBOL unit const &x() const;
	SGE_SYMBOL unit const &y() const;
	SGE_SYMBOL depth_type const &z() const;
	SGE_SYMBOL point const &pos() const;
	SGE_SYMBOL unit const &w() const;
	SGE_SYMBOL unit const &h() const;
	SGE_SYMBOL dim const &size() const;
	SGE_SYMBOL bool visible() const;
	SGE_SYMBOL rect_t const rect() const;
	SGE_SYMBOL point center() const;
	SGE_SYMBOL rotation_type rotation() const;
	SGE_SYMBOL funit radius() const;
	SGE_SYMBOL repetition_type repeat() const;
	SGE_SYMBOL color_t const color() const;
	SGE_SYMBOL rect_t const bounding_quad() const;
	SGE_SYMBOL circle const bounding_circle() const;
	SGE_SYMBOL point const rotation_center() const;
	SGE_SYMBOL texture::const_part_ptr const texture() const;
private:
	point                   pos_;
	dim                     size_;
	depth_type              z_;
	rotation_type           rotation_;
	texture::const_part_ptr tex;
	point                   rot_around_;
	repetition_type         repeat_;
	color_t                 color_;
	bool                    visible_;
	bool                    use_rot_around;
};

}
}

#endif
