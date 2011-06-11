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


#ifndef SGE_IMAGE2D_VIEW_MAKE_CONST_HPP_INCLUDED
#define SGE_IMAGE2D_VIEW_MAKE_CONST_HPP_INCLUDED

#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/optional_pitch.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/symbol.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/const_raw_pointer.hpp>

namespace sge
{
namespace image2d
{
namespace view
{

SGE_IMAGE2D_SYMBOL
image2d::view::const_object const
make_const(
	image::const_raw_pointer,
	image2d::dim const &,
	image::color::format::type,
	image2d::view::optional_pitch const &
);

}
}
}

#endif
