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


#include <sge/renderer/texture/filter/anisotropic/object.hpp>

sge::renderer::texture::filter::anisotropic::object::object(
	anisotropic::mip::type const _mip,
	anisotropic::level const _level
)
:
	mip_(_mip),
	level_(_level)
{
}

sge::renderer::texture::filter::anisotropic::mip::type
sge::renderer::texture::filter::anisotropic::object::mip() const
{
	return mip_;
}

sge::renderer::texture::filter::anisotropic::level const
sge::renderer::texture::filter::anisotropic::object::level() const
{
	return level_;
}

bool
sge::renderer::texture::filter::anisotropic::operator==(
	anisotropic::object const &_left,
	anisotropic::object const &_right
)
{
	return
		_left.mip() == _right.mip()
		&& _left.level() == _right.level();
}
