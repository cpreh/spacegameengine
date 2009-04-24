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
#include <sge/renderer/colors.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sge::sprite::point const
sge::sprite::defaults::pos(
	sge::sprite::point::null()
);

sge::texture::const_part_ptr const
sge::sprite::defaults::texture;


sge::sprite::dim const
sge::sprite::defaults::size(
	sge::sprite::texture_dim()
);

sge::sprite::color const
sge::sprite::defaults::color(
	sge::renderer::colors::white()
);

sge::sprite::depth_type const
sge::sprite::defaults::depth(
	static_cast<depth_type>(0)
);

sge::sprite::rotation_type const
sge::sprite::defaults::rotation(
	static_cast<rotation_type>(0)
);

bool const
sge::sprite::defaults::visible(
	true
);
