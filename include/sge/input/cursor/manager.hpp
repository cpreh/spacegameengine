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


#ifndef SGE_INPUT_CURSOR_MANAGER_HPP_INCLUDED
#define SGE_INPUT_CURSOR_MANAGER_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/discover_callback.hpp>
#include <sge/input/cursor/discover_event_fwd.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/remove_callback.hpp>
#include <sge/input/cursor/remove_event_fwd.hpp>
#include <sge/input/cursor/scroll_event_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	typedef
	fcppt::function<
		void (
			sge::input::cursor::object &,
			sge::input::cursor::button_event const &
		)
	>
	button_callback;

	typedef
	fcppt::function<
		void (
			sge::input::cursor::object &,
			sge::input::cursor::move_event const &
		)
	>
	move_callback;

	typedef
	fcppt::function<
		void (
			sge::input::cursor::object &,
			sge::input::cursor::scroll_event const &
		)
	>
	scroll_callback;

	SGE_INPUT_DETAIL_SYMBOL
	manager(
		sge::input::processor &,
		sge::input::cursor::discover_callback const &,
		sge::input::cursor::remove_callback const &,
		sge::input::cursor::manager::button_callback const &,
		sge::input::cursor::manager::move_callback const &,
		sge::input::cursor::manager::scroll_callback const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	~manager();

	typedef
	std::unordered_map<
		sge::input::cursor::object *,
		fcppt::signal::auto_connection_container
	>
	object_map;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::manager::object_map const &
	devices() const;
private:
	void
	discover(
		sge::input::cursor::discover_event const &
	);

	void
	remove(
		sge::input::cursor::remove_event const &
	);

	sge::input::cursor::manager::object_map objects_;

	sge::input::cursor::discover_callback const discover_callback_;

	sge::input::cursor::remove_callback const remove_callback_;

	sge::input::cursor::manager::button_callback const button_callback_;

	sge::input::cursor::manager::move_callback const move_callback_;

	sge::input::cursor::manager::scroll_callback const scroll_callback_;

	fcppt::signal::auto_connection_container const connections_;
};

}
}
}

#endif
