/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../shape_body_connection.hpp"
#include "../shapes/base.hpp"
#include "../body.hpp"
#include "../convert/to_bullet.hpp"

sge::bullet::shape_body_connection::shape_body_connection(
	shapes::base &_shape,
	sge::bullet::body &_body)
:
	shape_(
		_shape),
	body_(
		_body)
{
	// NOTE: This doesn't call shape_.meta_body(_body); because that's what bullet::body::add_shape should do
}

sge::bullet::body &
sge::bullet::shape_body_connection::body() const
{
	return 
		body_;
}
	
sge::bullet::shape_body_connection::~shape_body_connection()
{
	body_.remove_shape(
		shape_);
}
