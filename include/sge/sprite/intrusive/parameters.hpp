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
#ifndef SGE_SPRITE_INTRUSIVE_PARAMETERS_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_PARAMETERS_HPP_INCLUDED

#include <sge/sprite/intrusive/object_fwd.hpp>
#include <sge/sprite/intrusive/system_fwd.hpp>
#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/color.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/sprite/repetition_type.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace sprite
{
namespace intrusive
{

class parameters
{
public:
	SGE_SYMBOL parameters(
		system &,
		order);

	SGE_SYMBOL parameters &pos(point const &);
	SGE_SYMBOL parameters &texture(texture::const_part_ptr);
	SGE_SYMBOL parameters &size(dim const &);
	SGE_SYMBOL parameters &color(sge::sprite::color const &);
	SGE_SYMBOL parameters &depth(depth_type);
	SGE_SYMBOL parameters &rotation(rotation_type);
	SGE_SYMBOL parameters &visible(bool);

	SGE_SYMBOL operator object() const;
private:
	system &system_;
	order order_;
	point pos_;
	texture::const_part_ptr texture_;
	dim size_;
	sge::sprite::color color_;
	depth_type depth_;
	rotation_type rotation_;
	bool visible_;

};

}
}
}

#endif
