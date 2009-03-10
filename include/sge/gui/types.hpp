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


#ifndef SGE_GUI_TYPES_HPP_INCLUDED
#define SGE_GUI_TYPES_HPP_INCLUDED

#include <sge/sprite/unit.hpp>
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/rect.hpp>
#include <sge/sprite/fwd.hpp>
#include <sge/math/rect.hpp> // TODO
#include <sge/renderer/image_view.hpp>
#include <sge/renderer/image.hpp>
#include <sge/renderer/any_color.hpp>
#include <sge/shared_ptr.hpp>

namespace sge
{
namespace gui
{
typedef sprite::unit unit;
typedef sprite::point point;
typedef sprite::dim dim;
typedef sprite::rect rect;

typedef renderer::any_color color;
typedef renderer::rgba8_color internal_color;

typedef renderer::image_view image_view;
typedef renderer::const_image_view const_image_view;

typedef renderer::rgba8_image image;
typedef shared_ptr<image> image_ptr;
typedef shared_ptr<image const> const_image_ptr;
}
}

#endif
