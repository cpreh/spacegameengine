#ifndef SGE_CAMERA_PARAMETERS_HPP_INCLUDED
#define SGE_CAMERA_PARAMETERS_HPP_INCLUDED

#include <sge/camera/projection/object.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace camera
{
class parameters
{
public:
	explicit
	parameters(
		projection::object const &,
		renderer::scalar movement_speed,
		renderer::scalar rotation_speed,
		renderer::vector3 const &position,
		sge::input::keyboard::device &,
		sge::input::mouse::device &);

	projection::object const &
	projection() const;

	renderer::scalar
	movement_speed() const;

	renderer::scalar
	rotation_speed() const;

	renderer::vector3 const &
	position() const;

	sge::input::keyboard::device &
	keyboard() const;

	sge::input::mouse::device &
	mouse() const;
private:
	projection::object projection_;
	renderer::scalar movement_speed_;
	renderer::scalar rotation_speed_;
	renderer::vector3 position_;
	sge::input::keyboard::device &keyboard_;
	sge::input::mouse::device &mouse_;
};
}
}

#endif
