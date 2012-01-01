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


#ifndef SGE_D3D9_MAKE_PITCH_3D_HPP_INCLUDED
#define SGE_D3D9_MAKE_PITCH_3D_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image3d/dim.hpp>
#include <sge/image3d/view/optional_pitch.hpp>

namespace sge
{
namespace d3d9
{

sge::image3d::view::optional_pitch const
make_pitch_3d(
	D3DLOCKED_BOX const &,
	sge::image3d::dim const &,
	sge::image::color::format::type
);

}
}

#endif
