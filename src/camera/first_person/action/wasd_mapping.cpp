#include <sge/camera/first_person/action/wasd_mapping.hpp>
#include <sge/camera/first_person/action/mapping.hpp>

sge::camera::first_person::action::mapping const
sge::camera::first_person::action::wasd_mapping()
{
	return
		sge::camera::first_person::action::mapping(
			sge::camera::first_person::action::left(
				sge::camera::first_person::action::optional_key_code(
					sge::input::keyboard::key_code::a)),
			sge::camera::first_person::action::right(
				sge::camera::first_person::action::optional_key_code(
					sge::input::keyboard::key_code::d)),
			sge::camera::first_person::action::up(
				sge::camera::first_person::action::optional_key_code(
					sge::input::keyboard::key_code::space)),
			sge::camera::first_person::action::down(
				sge::camera::first_person::action::optional_key_code(
					sge::input::keyboard::key_code::lctrl)),
			sge::camera::first_person::action::forward(
				sge::camera::first_person::action::optional_key_code(
					sge::input::keyboard::key_code::w)),
			sge::camera::first_person::action::backward(
				sge::camera::first_person::action::optional_key_code(
					sge::input::keyboard::key_code::s)));
}
