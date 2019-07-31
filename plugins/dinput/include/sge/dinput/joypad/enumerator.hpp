//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_JOYPAD_ENUMERATOR_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_ENUMERATOR_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{

class enumerator
:
	public sge::dinput::device::enumerator
{
	FCPPT_NONCOPYABLE(
		enumerator
	);
public:
	explicit
	enumerator(
		IDirectInputDevice8 &
	);

	~enumerator()
	override;

	sge::input::joypad::absolute_axis_info_container::vector const &
	absolute_axis() const;

	sge::input::joypad::button_info_container::vector const &
	buttons() const;

	sge::input::joypad::relative_axis_info_container::vector const &
	relative_axis() const;

	sge::dinput::joypad::absolute_axis_map const &
	absolute_axis_map() const;

	sge::dinput::joypad::button_map const &
	button_map() const;

	sge::dinput::joypad::relative_axis_map const &
	relative_axis_map() const;
private:
	void
	dispatch(
		DIDEVICEOBJECTINSTANCE const &
	)
	override;

	IDirectInputDevice8 &device_;

	sge::input::joypad::absolute_axis_info_container::vector absolute_axis_;

	sge::input::joypad::button_info_container::vector buttons_;

	sge::input::joypad::relative_axis_info_container::vector relative_axis_;

	sge::dinput::joypad::absolute_axis_map absolute_axis_map_;

	sge::dinput::joypad::button_map button_map_;

	sge::dinput::joypad::relative_axis_map relative_axis_map_;
};

}
}
}

#endif
