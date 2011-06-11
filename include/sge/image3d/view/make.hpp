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


#ifndef SGE_IMAGE3D_VIEW_MAKE_HPP_INCLUDED
#define SGE_IMAGE3D_VIEW_MAKE_HPP_INCLUDED

#include <sge/image3d/view/object.hpp>
#include <sge/image3d/view/optional_pitch.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/symbol.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/raw_pointer.hpp>

namespace sge
{
namespace image3d
{
namespace view
{

SGE_IMAGE3D_SYMBOL
image3d::view::object const
make(
	image::raw_pointer,
	image3d::dim const &,
	image::color::format::type,
	image3d::view::optional_pitch const &
);

}
}
}

#endif
