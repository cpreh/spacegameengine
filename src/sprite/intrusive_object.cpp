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


#include <sge/sprite/intrusive_object.hpp>
#include <sge/sprite/intrusive_system.hpp>

sge::sprite::intrusive_object::intrusive_object(
	intrusive_system &sys,
	order_type const order_,
	point const &pos_,
	texture::const_part_ptr const vtex,
	dim const &size_,
	sprite::color const &color_,
	depth_type const z_,
	rotation_type const rotation_,
	bool const visible_)
:
	object(
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

sge::sprite::intrusive_object::intrusive_object(
	intrusive_object const &r)
:
	object(r),
	detail::object_base_hook(r),
	sys(r.sys),
	order_(r.order_)
{
	add_me();
}

sge::sprite::intrusive_object &
sge::sprite::intrusive_object::operator=(
	intrusive_object const &r)
{
	// TODO: what is necessary here?
	unlink();
	order_ = r.order_;
	detail::object_base_hook::operator=(r);	
	object::operator=(r);
	add_me();
	return *this;
}

void sge::sprite::intrusive_object::order(
	order_type const o)
{
	unlink();
	order_ = o;
	add_me();
}

sge::sprite::intrusive_object::order_type
sge::sprite::intrusive_object::order() const
{
	return order_;
}

void sge::sprite::intrusive_object::transfer(
	intrusive_system &nsys)
{
	unlink();
	sys = &nsys;
	add_me();
}

void sge::sprite::intrusive_object::add_me()
{
	sys->add(
		*this,
		order_);
}
