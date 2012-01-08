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


#include <sge/input/cursor/discover_event.hpp>
#include <sge/input/cursor/remove_event.hpp>
#include <sge/x11input/cursor/manager.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind/bind_member_function.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/operator/self.hpp>
#include <algorithm>
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
	FCPPT_ASSERT_ERROR(
		objects_.insert(
			static_cast<
				sge::x11input::cursor::object *
			>(
				&_discover.get()
			)
		)
		.second
	);
}

void
sge::x11input::cursor::manager::remove(
	sge::input::cursor::remove_event const &_remove
)
{
	FCPPT_ASSERT_ERROR(
		objects_.erase(
			static_cast<
				sge::x11input::cursor::object *
			>(
				&_remove.get()
			)
		)
		== 1u
	);
}

void
sge::x11input::cursor::manager::focus_in()
{
	entered_ = true;

	this->for_each_cursor(
		&x11input::cursor::object::on_focus_in
	);
}

void
sge::x11input::cursor::manager::focus_out()
{
	entered_ = false;

	this->for_each_cursor(
		&x11input::cursor::object::on_focus_out
	);
}

void
sge::x11input::cursor::manager::leave()
{
	this->for_each_cursor(
		&x11input::cursor::object::on_leave
	);
}

bool
sge::x11input::cursor::manager::entered() const
{
	return entered_;
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
		boost::phoenix::bind(
			_function,
			*boost::phoenix::arg_names::_1
		)
	);
}
