/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_DETAIL_CURSOR_DELEGATE_HPP_INCLUDED
#define SGE_GUI_DETAIL_CURSOR_DELEGATE_HPP_INCLUDED

#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/font/text/string.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
class cursor_delegate
{
	FCPPT_NONASSIGNABLE(
		cursor_delegate
	)
public:
	explicit cursor_delegate(
		sge::font::text::string &
	);

	sge::font::text::string::size_type
	pos() const;

	void
	key_callback(
		input::keyboard::key_event const &
	);
private:
	sge::font::text::string &text_;

	sge::font::text::string::size_type pos_;
};
}
}
}

#endif
