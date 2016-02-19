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


#ifndef SGE_INPUT_FOCUS_MOD_STATE_TRACKER_HPP_INCLUDED
#define SGE_INPUT_FOCUS_MOD_STATE_TRACKER_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/count.hpp>
#include <sge/input/focus/mod_state_tracker_fwd.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/input/key/mod_state_fwd.hpp>
#include <sge/input/key/modifier.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/enum_array_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace input
{
namespace focus
{

class mod_state_tracker
{
	FCPPT_NONCOPYABLE(
		mod_state_tracker
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	explicit
	mod_state_tracker(
		sge::input::focus::object &
	);

	SGE_INPUT_DETAIL_SYMBOL
	~mod_state_tracker();

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::key::mod_state
	mod_state() const;
private:
	typedef
	fcppt::container::enum_array<
		sge::input::key::modifier,
		sge::input::focus::count
	>
	count_array;

	static
	count_array
	null_array();

	count_array counts_;

	fcppt::signal::auto_connection const in_connection_;

	fcppt::signal::auto_connection const key_connection_;
};

}
}
}

#endif
