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



#ifndef SGE_SPRITE_DEFAULTS_HPP_INCLUDED
#define SGE_SPRITE_DEFAULTS_HPP_INCLUDED

#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/color.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace sprite
{
namespace defaults
{

SGE_SYMBOL point const pos();
SGE_SYMBOL sge::texture::const_part_ptr const texture();
SGE_SYMBOL dim const size();
SGE_SYMBOL sprite::color const color();
SGE_SYMBOL depth_type depth();
SGE_SYMBOL rotation_type rotation();
SGE_SYMBOL bool visible();

}
}
}

#endif
