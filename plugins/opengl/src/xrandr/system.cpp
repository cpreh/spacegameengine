//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/extension_fwd.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/opengl/xrandr/state_unique_ptr.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::opengl::xrandr::system::system(
	sge::opengl::xrandr::extension const &_extension
)
:
	extension_{
		_extension
	}
{
}

sge::opengl::xrandr::system::~system()
= default;

sge::opengl::xrandr::state_unique_ptr
sge::opengl::xrandr::system::create_state(
	sge::window::object_ref const _window
)
{
	return
		fcppt::make_unique_ptr<
			sge::opengl::xrandr::state
		>(
			extension_,
			_window
		);
}
