/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/texture/filter/normal/object.hpp>

sge::renderer::texture::filter::normal::object::object(
	normal::mag::type const _mag,
	normal::min::type const _min,
	normal::mip::type const _mip
)
:
	mag_(_mag),
	min_(_min),
	mip_(_mip)
{
}

sge::renderer::texture::filter::normal::mag::type
sge::renderer::texture::filter::normal::object::mag() const
{
	return mag_;
}

sge::renderer::texture::filter::normal::min::type
sge::renderer::texture::filter::normal::object::min() const
{
	return min_;
}

sge::renderer::texture::filter::normal::mip::type
sge::renderer::texture::filter::normal::object::mip() const
{
	return mip_;
}

bool
sge::renderer::texture::filter::normal::operator==(
	normal::object const &_left,
	normal::object const &_right
)
{
	return
		_left.mag() == _right.mag()
		&& _left.min() == _right.min()
		&& _left.mip() == _right.mip();
}
