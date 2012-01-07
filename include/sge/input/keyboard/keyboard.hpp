/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_INPUT_KEYBOARD_KEYBOARD_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_KEYBOARD_HPP_INCLUDED

#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/char_callback.hpp>
#include <sge/input/keyboard/char_event.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/char_function.hpp>
#include <sge/input/keyboard/char_signal.hpp>
#include <sge/input/keyboard/char_type.hpp>
#include <sge/input/keyboard/collector.hpp>
#include <sge/input/keyboard/collector_fwd.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/device_scoped_ptr.hpp>
#include <sge/input/keyboard/device_unique_ptr.hpp>
#include <sge/input/keyboard/digit.hpp>
#include <sge/input/keyboard/discover_callback.hpp>
#include <sge/input/keyboard/discover_event.hpp>
#include <sge/input/keyboard/discover_event_fwd.hpp>
#include <sge/input/keyboard/discover_function.hpp>
#include <sge/input/keyboard/discover_signal.hpp>
#include <sge/input/keyboard/is_alt.hpp>
#include <sge/input/keyboard/is_ctrl.hpp>
#include <sge/input/keyboard/is_shift.hpp>
#include <sge/input/keyboard/key_callback.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/input/keyboard/key_code_to_digit.hpp>
#include <sge/input/keyboard/key_code_to_string.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_function.hpp>
#include <sge/input/keyboard/key_repeat_callback.hpp>
#include <sge/input/keyboard/key_repeat_event.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_function.hpp>
#include <sge/input/keyboard/key_repeat_signal.hpp>
#include <sge/input/keyboard/key_signal.hpp>
#include <sge/input/keyboard/manager.hpp>
#include <sge/input/keyboard/mod_state.hpp>
#include <sge/input/keyboard/mod_state_fwd.hpp>
#include <sge/input/keyboard/modifier.hpp>
#include <sge/input/keyboard/optional_digit.hpp>
#include <sge/input/keyboard/optional_modifier.hpp>
#include <sge/input/keyboard/remove_callback.hpp>
#include <sge/input/keyboard/remove_event.hpp>
#include <sge/input/keyboard/remove_event_fwd.hpp>
#include <sge/input/keyboard/remove_function.hpp>
#include <sge/input/keyboard/remove_signal.hpp>
#include <sge/input/keyboard/to_modifier.hpp>

#endif
