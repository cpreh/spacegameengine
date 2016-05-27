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


#include <sge/input/exception.hpp>
#include <sge/wlinput/focus/keymap.hpp>
#include <sge/wlinput/focus/state.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::wlinput::focus::state::state(
	sge::wlinput::focus::keymap const &_keymap
)
:
	state_{
		::xkb_state_new(
			_keymap.get()
		)
	}
{
	if(
		state_
		==
		nullptr
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Failed to create xkb state")
			};
}

sge::wlinput::focus::state::state(
	state &&_other
)
:
	state_{
		_other.state_
	}
{
	_other.state_ =
		nullptr;
}

sge::wlinput::focus::state &
sge::wlinput::focus::state::operator=(
	state &&_other
)
{
	std::swap(
		state_,
		_other.state_
	);

	return
		*this;
}

sge::wlinput::focus::state::~state()
{
	// Ok to call this on nullptr
	::xkb_state_unref(
		state_
	);
}

xkb_state *
sge::wlinput::focus::state::get() const
{
	return
		state_;
}
