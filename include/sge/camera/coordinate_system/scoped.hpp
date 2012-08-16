#ifndef SGE_CAMERA_COORDINATE_SYSTEM_SCOPED_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_SCOPED_HPP_INCLUDED

#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/has_mutable_coordinate_system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <sge/camera/symbol.hpp>

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
	SGE_CAMERA_SYMBOL
	scoped(
		sge::camera::has_mutable_coordinate_system &,
		sge::camera::coordinate_system::object const &);

	SGE_CAMERA_SYMBOL
	~scoped();
private:
	sge::camera::has_mutable_coordinate_system &camera_;
	sge::camera::coordinate_system::object old_coordinates_;
};
}
}
}

#endif
