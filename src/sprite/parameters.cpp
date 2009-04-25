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
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/defaults.hpp>
#include <sge/sprite/texture_dim.hpp>

sge::sprite::parameters::parameters()
:
	pos_(defaults::pos),
	texture_(defaults::texture),
	size_(defaults::size),
	color_(defaults::color),
	depth_(defaults::depth),
	rotation_(defaults::rotation),
	visible_(defaults::visible)
{}

sge::sprite::parameters &sge::sprite::parameters::pos(
	point const &_pos)
{
	pos_ = _pos;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::texture(
	texture::const_part_ptr const _texture)
{
	texture_ = _texture;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::size(
	dim const &_size)
{
	size_ = _size;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::color(
	sge::sprite::color const &_color)
{
	color_ = _color;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::depth(
	depth_type const _depth)
{
	depth_ = _depth;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::rotation(
	rotation_type const _rotation)
{
	rotation_ = _rotation;
	return *this;
}

sge::sprite::parameters &sge::sprite::parameters::visible(
	bool const _visible)
{
	visible_ = _visible;
	return *this;
}

sge::sprite::parameters::operator sge::sprite::object() const
{
	return object(
		pos_,
		texture_,
		size_ == texture_dim() && !texture_
		? dim::null()
		: size_,
		color_,
		depth_,
		rotation_,
		visible_
	);
}
