/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SYSTEMS_DETAIL_INPUT_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_INPUT_HPP_INCLUDED

#include <sge/systems/input.hpp>
#include <sge/systems/symbol.hpp>
#include <sge/systems/detail/input_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

class input
{
	FCPPT_NONASSIGNABLE(
		input
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		bool,
		cursor_demuxer
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		bool,
		keyboard_collector
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		bool,
		mouse_collector
	);

	SGE_SYSTEMS_SYMBOL
	input(
		sge::systems::input const &,
		sge::systems::detail::input::cursor_demuxer,
		sge::systems::detail::input::keyboard_collector,
		sge::systems::detail::input::mouse_collector
	);

	sge::systems::input const &
	parameters() const;

	sge::systems::detail::input::cursor_demuxer const
	get_cursor_demuxer() const;

	sge::systems::detail::input::keyboard_collector const
	get_keyboard_collector() const;

	sge::systems::detail::input::mouse_collector const
	get_mouse_collector() const;
private:
	sge::systems::input const parameters_;

	sge::systems::detail::input::cursor_demuxer const cursor_demuxer_;

	sge::systems::detail::input::keyboard_collector const keyboard_collector_;

	sge::systems::detail::input::mouse_collector const mouse_collector_;
};

}
}
}

#endif
