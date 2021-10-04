//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_CURSOR_DATA_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_DATA_HPP_INCLUDED

#include <sge/input/cursor/optional_position.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge::wlinput::cursor
{

struct data
{
	FCPPT_NONMOVABLE(
		data
	);

	data(
		fcppt::reference<
			sge::wlinput::cursor::object
		>,
		awl::backends::wayland::window::object_ref,
		awl::event::container_reference
	);

	~data() = default;

	fcppt::reference<
		sge::wlinput::cursor::object
	> const cursor_; // NOLINT(misc-non-private-member-variables-in-classes)

	awl::backends::wayland::window::object_ref const window_; // NOLINT(misc-non-private-member-variables-in-classes)

	awl::event::container_reference const events_; // NOLINT(misc-non-private-member-variables-in-classes)

	sge::input::cursor::optional_position position_; // NOLINT(misc-non-private-member-variables-in-classes)
};

}

#endif
