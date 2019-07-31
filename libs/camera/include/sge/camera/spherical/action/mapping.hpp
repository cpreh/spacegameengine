//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_SPHERICAL_ACTION_MAPPING_HPP_INCLUDED
#define SGE_CAMERA_SPHERICAL_ACTION_MAPPING_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
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
	SGE_CAMERA_DETAIL_SYMBOL
	explicit
	mapping(
		action::increase_azimuth const &,
		action::decrease_azimuth const &,
		action::increase_inclination const &,
		action::decrease_inclination const &,
		action::increase_radius const &,
		action::decrease_radius const &);

	SGE_CAMERA_DETAIL_SYMBOL
	action::increase_azimuth const &
	increase_azimuth() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::decrease_azimuth const &
	decrease_azimuth() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::increase_inclination const &
	increase_inclination() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::decrease_inclination const &
	decrease_inclination() const;

	SGE_CAMERA_DETAIL_SYMBOL
	action::increase_radius const &
	increase_radius() const;

	SGE_CAMERA_DETAIL_SYMBOL
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

