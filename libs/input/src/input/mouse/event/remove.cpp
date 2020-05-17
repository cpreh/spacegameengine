//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/base.hpp>
#include <sge/input/mouse/event/remove.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::input::mouse::event::remove::remove(
	sge::input::mouse::shared_ptr _mouse
)
:
	sge::input::mouse::event::base{
		std::move(
			_mouse
		)
	}
{
}

sge::input::mouse::event::remove::~remove()
= default;
