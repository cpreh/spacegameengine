/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/remove_event.hpp>
#include <sge/x11input/cursor/entered.hpp>
#include <sge/x11input/cursor/manager.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/static_downcast_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::x11input::cursor::manager::manager()
:
	objects_(),
	entered_(
		false
	)
{
}

sge::x11input::cursor::manager::~manager()
{
}

void
sge::x11input::cursor::manager::discover(
	sge::input::cursor::discover_event const &_discover
)
{
	typedef std::pair<
		object_set::iterator,
		bool
	> insert_return_type;

	insert_return_type const ret(
		objects_.insert(
			fcppt::cast::static_downcast_ptr<
				sge::x11input::cursor::object *
			>(
				&_discover.get()
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		ret.second
	);

	if(
		entered_.get()
	)
		(*ret.first)->on_focus_in();
}

void
sge::x11input::cursor::manager::remove(
	sge::input::cursor::remove_event const &_remove
)
{
	FCPPT_ASSERT_ERROR(
		objects_.erase(
			fcppt::cast::static_downcast_ptr<
				sge::x11input::cursor::object *
			>(
				&_remove.get()
			)
		)
		==
		1u
	);
}

void
sge::x11input::cursor::manager::focus_in()
{
	entered_ =
		sge::x11input::cursor::entered(
			true
		);

	this->for_each_cursor(
		&sge::x11input::cursor::object::on_focus_in
	);
}

void
sge::x11input::cursor::manager::focus_out()
{
	entered_ =
		sge::x11input::cursor::entered(
			false
		);

	this->for_each_cursor(
		&sge::x11input::cursor::object::on_focus_out
	);
}

sge::x11input::cursor::entered const
sge::x11input::cursor::manager::entered() const
{
	return
		entered_;
}

template<
	typename Function
>
void
sge::x11input::cursor::manager::for_each_cursor(
	Function const &_function
)
{
	std::for_each(
		objects_.begin(),
		objects_.end(),
		[
			&_function
		](
			sge::x11input::cursor::object *const _obj
		)
		{
			(_obj->*_function)();
		}
	);
}
