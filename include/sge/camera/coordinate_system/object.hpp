#ifndef SGE_CAMERA_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED
#define SGE_CAMERA_COORDINATE_SYSTEM_OBJECT_HPP_INCLUDED

#include <sge/camera/symbol.hpp>
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
	SGE_CAMERA_SYMBOL
	explicit
	object(
		coordinate_system::right const &,
		coordinate_system::up const &,
		coordinate_system::forward const &,
		coordinate_system::position const &);

	SGE_CAMERA_SYMBOL
	coordinate_system::right const &
	right() const;

	SGE_CAMERA_SYMBOL
	void
	right(
		coordinate_system::right const &);

	SGE_CAMERA_SYMBOL
	coordinate_system::up const &
	up() const;

	SGE_CAMERA_SYMBOL
	void
	up(
		coordinate_system::up const &);

	SGE_CAMERA_SYMBOL
	coordinate_system::forward const &
	forward() const;

	SGE_CAMERA_SYMBOL
	void
	forward(
		coordinate_system::forward const &);

	SGE_CAMERA_SYMBOL
	coordinate_system::position const &
	position() const;

	SGE_CAMERA_SYMBOL
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

