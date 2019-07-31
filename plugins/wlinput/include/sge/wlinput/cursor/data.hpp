//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_CURSOR_DATA_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_DATA_HPP_INCLUDED

#include <sge/input/cursor/optional_position.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace wlinput
{
namespace cursor
{

struct data
{
	FCPPT_NONCOPYABLE(
		data
	);

	data(
		sge::wlinput::cursor::object &,
		awl::backends::wayland::window::object const &,
		awl::event::container_reference
	);

	~data();

	sge::wlinput::cursor::object &cursor_;

	awl::backends::wayland::window::object const &window_;

	awl::event::container_reference const events_;

	sge::input::cursor::optional_position position_;
};

}
}
}

#endif
