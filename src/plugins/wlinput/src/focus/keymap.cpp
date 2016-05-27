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
#include <sge/wlinput/xkb_context.hpp>
#include <sge/wlinput/focus/keymap.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::wlinput::focus::keymap::keymap(
	sge::wlinput::xkb_context const &_context,
	char const *const _string
)
:
	keymap_{
		::xkb_keymap_new_from_string(
			_context.get(),
			_string,
			XKB_KEYMAP_FORMAT_TEXT_V1,
			XKB_KEYMAP_COMPILE_NO_FLAGS
		)
	}
{
	if(
		keymap_
		==
		nullptr
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Cannot create keymap")
			};
}

sge::wlinput::focus::keymap::keymap(
	keymap &&_other
)
:
	keymap_{
		_other.keymap_
	}
{
	_other.keymap_ =
		nullptr;
}

sge::wlinput::focus::keymap &
sge::wlinput::focus::keymap::operator=(
	keymap &&_other
)
{
	std::swap(
		keymap_,
		_other.keymap_
	);

	return
		*this;
}

sge::wlinput::focus::keymap::~keymap()
{
	::xkb_keymap_unref(
		keymap_
	);
}

xkb_keymap *
sge::wlinput::focus::keymap::get() const
{
	return
		keymap_;
}
