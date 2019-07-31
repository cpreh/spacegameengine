//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED

#include <sge/camera/coordinate_system/forward.hpp>
#include <sge/camera/coordinate_system/position.hpp>
#include <sge/camera/coordinate_system/right.hpp>
#include <sge/camera/coordinate_system/up.hpp>
#include <sge/camera/detail/symbol.hpp>


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
	object(
		sge::camera::coordinate_system::right const &,
		sge::camera::coordinate_system::up const &,
		sge::camera::coordinate_system::forward const &,
		sge::camera::coordinate_system::position const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::right const &
	right() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	right(
		sge::camera::coordinate_system::right const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::up const &
	up() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	up(
		sge::camera::coordinate_system::up const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::forward const &
	forward() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	forward(
		sge::camera::coordinate_system::forward const &
	);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::position const &
	position() const;

	SGE_CAMERA_DETAIL_SYMBOL
	void
	position(
		sge::camera::coordinate_system::position const &
	);
private:
	sge::camera::coordinate_system::right right_;

	sge::camera::coordinate_system::up up_;

	sge::camera::coordinate_system::forward forward_;

	sge::camera::coordinate_system::position position_;
};

}
}
}

#endif

