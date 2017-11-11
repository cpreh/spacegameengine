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


#ifndef SGE_INPUT_KEYBOARD_EVENT_KEY_HPP_INCLUDED
#define SGE_INPUT_KEYBOARD_EVENT_KEY_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/key.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/base.hpp>
#include <sge/input/keyboard/event/key_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace input
{
namespace keyboard
{
namespace event
{

class SGE_CORE_DETAIL_CLASS_SYMBOL key
:
	public sge::input::keyboard::event::base
{
	FCPPT_NONCOPYABLE(
		key
	);
public:
	SGE_INPUT_DETAIL_SYMBOL
	key(
		sge::input::keyboard::shared_ptr,
		sge::input::keyboard::key const &,
		sge::input::key::pressed
	);

	SGE_INPUT_DETAIL_SYMBOL
	~key();

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::keyboard::key const &
	get() const;

	SGE_INPUT_DETAIL_SYMBOL
	bool
	pressed() const;
private:
	sge::input::keyboard::key const key_;

	sge::input::key::pressed const pressed_;
};

}
}
}
}

#endif
