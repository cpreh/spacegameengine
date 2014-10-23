/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_LOOK_DOWN_POSITIVE_Z_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_LOOK_DOWN_POSITIVE_Z_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/spherical/coordinate_system/object_fwd.hpp>
#include <sge/camera/spherical/coordinate_system/radius.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{
namespace coordinate_system
{
SGE_CAMERA_DETAIL_SYMBOL
spherical::coordinate_system::object const
look_down_positive_z(
	spherical::coordinate_system::radius const &);
}
}
}
}

#endif

