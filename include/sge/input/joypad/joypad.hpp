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


#ifndef SGE_INPUT_JOYPAD_JOYPAD_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_JOYPAD_HPP_INCLUDED

#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_callback.hpp>
#include <sge/input/joypad/absolute_axis_event.hpp>
#include <sge/input/joypad/absolute_axis_event_fwd.hpp>
#include <sge/input/joypad/absolute_axis_function.hpp>
#include <sge/input/joypad/absolute_axis_fwd.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/absolute_axis_info_container_fwd.hpp>
#include <sge/input/joypad/absolute_axis_info_fwd.hpp>
#include <sge/input/joypad/absolute_axis_signal.hpp>
#include <sge/input/joypad/axis_code.hpp>
#include <sge/input/joypad/axis_code_to_string.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/button_event.hpp>
#include <sge/input/joypad/button_event_fwd.hpp>
#include <sge/input/joypad/button_function.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/button_info_container_fwd.hpp>
#include <sge/input/joypad/button_info_fwd.hpp>
#include <sge/input/joypad/button_signal.hpp>
#include <sge/input/joypad/collector_fwd.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/device_fwd.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event.hpp>
#include <sge/input/joypad/discover_event_fwd.hpp>
#include <sge/input/joypad/discover_function.hpp>
#include <sge/input/joypad/discover_signal.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/manager.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/relative_axis_callback.hpp>
#include <sge/input/joypad/relative_axis_event.hpp>
#include <sge/input/joypad/relative_axis_event_fwd.hpp>
#include <sge/input/joypad/relative_axis_function.hpp>
#include <sge/input/joypad/relative_axis_fwd.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/relative_axis_info_container_fwd.hpp>
#include <sge/input/joypad/relative_axis_info_fwd.hpp>
#include <sge/input/joypad/relative_axis_signal.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event.hpp>
#include <sge/input/joypad/remove_event_fwd.hpp>
#include <sge/input/joypad/remove_function.hpp>
#include <sge/input/joypad/remove_signal.hpp>

#endif
