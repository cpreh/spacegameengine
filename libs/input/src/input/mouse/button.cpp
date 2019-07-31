//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_code.hpp>
#include <sge/input/mouse/button_id.hpp>


sge::input::mouse::button::button(
	sge::input::mouse::button_code const _code,
	sge::input::mouse::button_id const _id
)
:
	code_(
		_code
	),
	id_(
		_id
	)
{
}

sge::input::mouse::button_code
sge::input::mouse::button::code() const
{
	return
		code_;
}

sge::input::mouse::button_id
sge::input::mouse::button::id() const
{
	return
		id_;
}
