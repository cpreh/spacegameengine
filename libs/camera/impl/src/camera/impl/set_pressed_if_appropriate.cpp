//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/impl/set_pressed_if_appropriate.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/optional_code.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::camera::impl::set_pressed_if_appropriate(
	bool &_result,
	sge::input::key::optional_code const &_optional_key,
	sge::input::keyboard::event::key const &_key_event
)
{
	fcppt::optional::maybe_void(
		_optional_key,
		[
			&_key_event,
			&_result
		](
			sge::input::key::code const _code
		)
		{
			if(
				_code
				==
				_key_event.get().code()
			)
				_result =
					_key_event.pressed();
		}
	);
}
