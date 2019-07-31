//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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

