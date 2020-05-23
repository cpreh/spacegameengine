//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/event/base.hpp>
#include <awl/window/reference.hpp>
#include <awl/window/event/base.hpp>


sge::renderer::event::base::base(
	awl::window::reference const _window
)
:
	awl::window::event::base{
		_window
	}
{
}

sge::renderer::event::base::~base()
= default;
