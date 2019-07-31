//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_COORDINATE_SYSTEM_SCOPED_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_SCOPED_HPP_INCLUDED

#include <sge/camera/has_mutable_coordinate_system_fwd.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace camera
{
namespace coordinate_system
{
class scoped
{
FCPPT_NONCOPYABLE(
	scoped);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	scoped(
		sge::camera::has_mutable_coordinate_system &,
		sge::camera::coordinate_system::object const &);

	SGE_CAMERA_DETAIL_SYMBOL
	~scoped();
private:
	sge::camera::has_mutable_coordinate_system &camera_;
	sge::camera::coordinate_system::object old_coordinates_;
};
}
}
}

#endif
