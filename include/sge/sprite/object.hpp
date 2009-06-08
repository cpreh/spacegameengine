/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/color.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/sprite/repetition_type.hpp>
#include <sge/sprite/unit.hpp>
#include <sge/sprite/circle.hpp>
#include <sge/sprite/rect.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace sprite
{

class object {
public:
	SGE_SYMBOL object(
		point const &,
		texture::const_part_ptr,
		dim const &,
		sprite::color const &,
		depth_type,
		rotation_type,
		bool visible);
	
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
	SGE_SYMBOL void rotate_around(point const &);
	SGE_SYMBOL void rotate_around();
	SGE_SYMBOL void repeat(repetition_type);
	SGE_SYMBOL void color(sprite::color const &);
	SGE_SYMBOL void center(point const &);
	
	SGE_SYMBOL unit const &x() const;
	SGE_SYMBOL unit const &y() const;
	SGE_SYMBOL depth_type const &z() const;
	SGE_SYMBOL point const &pos() const;
	SGE_SYMBOL unit const &w() const;
	SGE_SYMBOL unit const &h() const;
	SGE_SYMBOL dim const &size() const;
	SGE_SYMBOL bool visible() const;
	SGE_SYMBOL sprite::rect const rect() const;
	SGE_SYMBOL point const center() const;
	SGE_SYMBOL rotation_type rotation() const;
	SGE_SYMBOL funit radius() const;
	SGE_SYMBOL repetition_type repeat() const;
	SGE_SYMBOL sprite::color const color() const;
	SGE_SYMBOL sprite::rect const bounding_quad() const;
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
	sprite::color           color_;
	bool                    visible_;
	bool                    use_rot_around;
};

}
}

#endif
