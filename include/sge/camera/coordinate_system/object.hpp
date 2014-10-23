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


#ifndef SGE_CAMERA_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/coordinate_system/forward.hpp>
#include <sge/camera/coordinate_system/position.hpp>
#include <sge/camera/coordinate_system/right.hpp>
#include <sge/camera/coordinate_system/up.hpp>
#include <fcppt/math/vector/object_impl.hpp>


namespace sge
{
namespace camera
{
namespace coordinate_system
{
/**
\brief Represents a coordinate system with three axes and a position
\ingroup sgecamera
*/
class object
{
public:
	SGE_CAMERA_DETAIL_SYMBOL
	explicit
	object(
		coordinate_system::right const &,
		coordinate_system::up const &,
		coordinate_system::forward const &,
		coordinate_system::position const &);

	SGE_CAMERA_DETAIL_SYMBOL
	coordinate_system::right const &
	right() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	right(
		coordinate_system::right const &);

	SGE_CAMERA_DETAIL_SYMBOL
	coordinate_system::up const &
	up() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	up(
		coordinate_system::up const &);

	SGE_CAMERA_DETAIL_SYMBOL
	coordinate_system::forward const &
	forward() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	forward(
		coordinate_system::forward const &);

	SGE_CAMERA_DETAIL_SYMBOL
	coordinate_system::position const &
	position() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	position(
		coordinate_system::position const &);
private:
	coordinate_system::right right_;
	coordinate_system::up up_;
	coordinate_system::forward forward_;
	coordinate_system::position position_;
};
}
}
}

#endif

