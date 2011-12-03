/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/any/object.hpp>
#include <mizuiro/color/operators/equal.hpp>
#include <fcppt/variant/equal.hpp>
#include <fcppt/variant/object_impl.hpp>


sge::image::color::any::object::object(
	variant const &_variant
)
:
	variant_(_variant)
{
}

sge::image::color::any::object::object(
	object const &_other
)
:
	variant_(_other.variant_)
{
}

sge::image::color::any::object &
sge::image::color::any::object::operator=(
	object const &_other
)
{
	if(
		this != &_other
	)
		variant_ = _other.variant_;

	return *this;
}

sge::image::color::any::object::~object()
{
}

sge::image::color::any::object::variant const &
sge::image::color::any::object::get() const
{
	return variant_;
}

bool
sge::image::color::any::operator==(
	any::object const &_left,
	any::object const &_right
)
{
	return
		_left.get() == _right.get();
}
