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


#ifndef SGE_CAMERA_SPHERICAL_ACTION_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_ACTION_MAPPING_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
#include <sge/camera/spherical/action/decrease_azimuth.hpp>
#include <sge/camera/spherical/action/decrease_inclination.hpp>
#include <sge/camera/spherical/action/decrease_radius.hpp>
#include <sge/camera/spherical/action/increase_azimuth.hpp>
#include <sge/camera/spherical/action/increase_inclination.hpp>
#include <sge/camera/spherical/action/increase_radius.hpp>


namespace sge
{
namespace camera
{
namespace spherical
{
namespace action
{
/**
\brief A mapping from camera "actions" to key codes
\ingroup sgecamera
*/
class mapping
{
public:
	SGE_CAMERA_SYMBOL
	explicit
	mapping(
		action::increase_azimuth const &,
		action::decrease_azimuth const &,
		action::increase_inclination const &,
		action::decrease_inclination const &,
		action::increase_radius const &,
		action::decrease_radius const &);

	SGE_CAMERA_SYMBOL
	action::increase_azimuth const &
	increase_azimuth() const;

	SGE_CAMERA_SYMBOL
	action::decrease_azimuth const &
	decrease_azimuth() const;

	SGE_CAMERA_SYMBOL
	action::increase_inclination const &
	increase_inclination() const;

	SGE_CAMERA_SYMBOL
	action::decrease_inclination const &
	decrease_inclination() const;

	SGE_CAMERA_SYMBOL
	action::increase_radius const &
	increase_radius() const;

	SGE_CAMERA_SYMBOL
	action::decrease_radius const &
	decrease_radius() const;
private:
	action::increase_azimuth increase_azimuth_;
	action::decrease_azimuth decrease_azimuth_;
	action::increase_inclination increase_inclination_;
	action::decrease_inclination decrease_inclination_;
	action::increase_radius increase_radius_;
	action::decrease_radius decrease_radius_;
};
}
}
}
}

#endif

