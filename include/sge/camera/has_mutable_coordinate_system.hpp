#ifndef SGE_CAMERA_HAS_MUTABLE_COORDINATE_SYSTEM_HPP_INCLUDED
#define SGE_CAMERA_HAS_MUTABLE_COORDINATE_SYSTEM_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/camera/base.hpp>
#include <sge/camera/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace camera
{
class SGE_CLASS_SYMBOL has_mutable_coordinate_system
:
	public virtual sge::camera::base
{
FCPPT_NONCOPYABLE(
	has_mutable_coordinate_system);
protected:
	SGE_CAMERA_SYMBOL
	explicit
	has_mutable_coordinate_system();
public:
	virtual void
	update_coordinate_system(
		sge::camera::coordinate_system::object const &) = 0;

	SGE_CAMERA_SYMBOL
	virtual ~has_mutable_coordinate_system() = 0;
};
}
}

#endif
