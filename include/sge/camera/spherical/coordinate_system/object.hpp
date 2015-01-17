/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/spherical/coordinate_system/azimuth.hpp>
#include <sge/camera/spherical/coordinate_system/inclination.hpp>
#include <sge/camera/spherical/coordinate_system/radius.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{
namespace coordinate_system
{
class object
{
public:
	SGE_CAMERA_DETAIL_SYMBOL
	explicit
	object(
		spherical::coordinate_system::azimuth const &,
		spherical::coordinate_system::inclination const &,
		spherical::coordinate_system::radius const &);

	SGE_CAMERA_DETAIL_SYMBOL
	spherical::coordinate_system::azimuth const &
	azimuth() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	azimuth(
		spherical::coordinate_system::azimuth const &);

	SGE_CAMERA_DETAIL_SYMBOL
	spherical::coordinate_system::inclination const &
	inclination() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	inclination(
		spherical::coordinate_system::inclination const &);

	SGE_CAMERA_DETAIL_SYMBOL
	spherical::coordinate_system::radius const &
	radius() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	radius(
		spherical::coordinate_system::radius const &);
private:
	spherical::coordinate_system::azimuth azimuth_;
	spherical::coordinate_system::inclination inclination_;
	spherical::coordinate_system::radius radius_;
};
}
}
}
}

#endif

