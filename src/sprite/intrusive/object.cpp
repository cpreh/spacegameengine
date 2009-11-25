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


#include <sge/sprite/intrusive/object.hpp>
#include <sge/sprite/intrusive/system.hpp>

sge::sprite::intrusive::object::object(
	intrusive::system &sys,
	order_type const order_,
	point const &pos_,
	texture::const_part_ptr const vtex,
	dim const &size_,
	sprite::color const &color_,
	depth_type const z_,
	rotation_type const rotation_,
	bool const visible_)
:
	sprite::object(
		pos_,
		vtex,
		size_,
		color_,
		z_,
		rotation_,
		visible_),
	sys(&sys),
	order_(order_)
{
	add_me();
}

sge::sprite::intrusive::object::object(
	intrusive::object const &r)
:
	sprite::object(r),
	detail::object_base_hook(r),
	sys(r.sys),
	order_(r.order_)
{
	add_me();
}

sge::sprite::intrusive::object &
sge::sprite::intrusive::object::operator=(
	intrusive::object const &r)
{
	// TODO: what is necessary here?
	unlink();
	order_ = r.order_;
	detail::object_base_hook::operator=(r);
	sprite::object::operator=(r);
	add_me();
	return *this;
}

void sge::sprite::intrusive::object::order(
	order_type const o)
{
	unlink();
	order_ = o;
	add_me();
}

sge::sprite::intrusive::object::order_type
sge::sprite::intrusive::object::order() const
{
	return order_;
}

void sge::sprite::intrusive::object::transfer(
	intrusive::system &nsys)
{
	unlink();
	sys = &nsys;
	add_me();
}

void sge::sprite::intrusive::object::add_me()
{
	sys->add(
		*this,
		order_);
}
