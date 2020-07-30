//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/sdlinput/mouse/device.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>


sge::sdlinput::mouse::device::device(
	sge::window::object_ref const _window
)
:
	sge::input::mouse::device{},
	window_{
		_window
	},
	info_{
		// TODO(philipp): Can SDL provide any of this information?
		sge::input::mouse::axis_info_container{
			sge::input::mouse::axis_info_container::vector{}
		},
		sge::input::mouse::button_info_container{
			sge::input::mouse::button_info_container::vector{}
		},
		sge::input::info::name{
			fcppt::string{
				FCPPT_TEXT("SDL2 mouse")
			}
		}
	}
{
}

sge::sdlinput::mouse::device::~device()
= default;

sge::window::object &
sge::sdlinput::mouse::device::window() const
{
	return
		this->window_.get();
}

sge::input::mouse::info const &
sge::sdlinput::mouse::device::info() const
{
	return
		this->info_;
}
