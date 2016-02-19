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


#include <sge/input/key/action.hpp>
#include <sge/input/key/action_callback.hpp>
#include <sge/input/key/callback.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/pressed.hpp>


sge::input::key::callback
sge::input::key::action(
	sge::input::key::code const _code,
	sge::input::key::action_callback const &_action
)
{
	return
		sge::input::key::callback(
			[
				_code,
				_action
			](
				sge::input::key::code const _cur_code,
				sge::input::key::pressed const _pressed
			)
			{
				if(
					_pressed.get()
					&&
					_cur_code
					==
					_code
				)
					_action();
			}
		);
}
