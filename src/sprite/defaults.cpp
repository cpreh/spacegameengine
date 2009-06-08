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


#include <sge/sprite/defaults.hpp>
#include <sge/sprite/texture_dim.hpp>
#include <sge/image/color/colors.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sge::sprite::point const
sge::sprite::defaults::pos()
{
	return	sge::sprite::point::null();
}

sge::texture::const_part_ptr const
sge::sprite::defaults::texture()
{
	return sge::texture::const_part_ptr();
}

sge::sprite::dim const
sge::sprite::defaults::size()
{
	return sge::sprite::texture_dim();
}

sge::sprite::color const
sge::sprite::defaults::color()
{
	return sge::image::color::colors::white();
}

sge::sprite::depth_type
sge::sprite::defaults::depth()
{
	return static_cast<depth_type>(0);
}

sge::sprite::rotation_type
sge::sprite::defaults::rotation()
{
	return static_cast<rotation_type>(0);
}

bool sge::sprite::defaults::visible()
{
	return true;
}
