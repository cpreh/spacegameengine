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
#include <sge/input/focus/mod_state_tracker_fwd.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/base_fwd.hpp>
#include <sge/input/key/mod_state_fwd.hpp>
#include <sge/input/key/modifier.hpp>
#include <sge/input/key/pressed.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/shared_ptr_std_hash.hpp>
#include <fcppt/enum/array_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


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
	mod_state_tracker();

	SGE_INPUT_DETAIL_SYMBOL
	~mod_state_tracker();

	SGE_INPUT_DETAIL_SYMBOL
	void
	event(
		sge::input::focus::event::base const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::key::mod_state
	mod_state(
		sge::input::focus::shared_ptr const &
	) const;
private:
	typedef
	fcppt::enum_::array<
		sge::input::key::modifier,
		sge::input::key::pressed
	>
	pressed_array;

	typedef
	std::unordered_map<
		sge::input::focus::shared_ptr,
		pressed_array
	>
	map_type;

	map_type map_;
};

}
}
}

#endif
