/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_FOCUS_MANAGER_HPP_INCLUDED
#define SGE_INPUT_FOCUS_MANAGER_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/char_event_fwd.hpp>
#include <sge/input/focus/discover_callback.hpp>
#include <sge/input/focus/discover_event_fwd.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_event_fwd.hpp>
#include <sge/input/focus/key_event_fwd.hpp>
#include <sge/input/focus/key_repeat_event_fwd.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_event_fwd.hpp>
#include <sge/input/focus/remove_callback.hpp>
#include <sge/input/focus/remove_event_fwd.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/optional_auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{
namespace focus
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
			sge::input::focus::object &,
			sge::input::focus::char_event const &
		)
	>
	char_callback;

	typedef
	fcppt::function<
		void (
			sge::input::focus::object &,
			sge::input::focus::key_event const &
		)
	>
	key_callback;

	typedef
	fcppt::function<
		void (
			sge::input::focus::object &,
			sge::input::focus::key_repeat_event const &
		)
	>
	key_repeat_callback;

	typedef
	fcppt::function<
		void (
			sge::input::focus::object &,
			sge::input::focus::in_event const &
		)
	>
	in_callback;

	typedef
	fcppt::function<
		void (
			sge::input::focus::object &,
			sge::input::focus::out_event const &
		)
	>
	out_callback;

	SGE_INPUT_DETAIL_SYMBOL
	manager(
		sge::input::processor &,
		sge::input::focus::discover_callback const &,
		sge::input::focus::remove_callback const &,
		char_callback const &,
		key_callback const &,
		key_repeat_callback const &,
		in_callback const &,
		out_callback const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	~manager();

	typedef
	std::unordered_map<
		fcppt::reference<
			sge::input::focus::object
		>,
		fcppt::signal::auto_connection_container
	>
	focus_map;

	SGE_INPUT_DETAIL_SYMBOL
	focus_map const &
	objects() const;
private:
	void
	discover(
		sge::input::focus::discover_event const &
	);

	void
	remove(
		sge::input::focus::remove_event const &
	);

	focus_map objects_;

	sge::input::focus::discover_callback const discover_callback_;

	sge::input::focus::remove_callback const remove_callback_;

	char_callback const char_callback_;

	key_callback const key_callback_;

	key_repeat_callback const key_repeat_callback_;

	in_callback const in_callback_;

	out_callback const out_callback_;

	fcppt::signal::optional_auto_connection const discover_connection_;

	fcppt::signal::optional_auto_connection const remove_connection_;
};

}
}
}

#endif
