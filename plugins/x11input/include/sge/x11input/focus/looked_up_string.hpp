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


#ifndef SGE_X11INPUT_FOCUS_LOOKED_UP_STRING_HPP_INCLUDED
#define SGE_X11INPUT_FOCUS_LOOKED_UP_STRING_HPP_INCLUDED

#include <sge/input/key/code.hpp>
#include <sge/x11input/focus/char_vector.hpp>
#include <sge/x11input/focus/looked_up_string_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace x11input
{
namespace focus
{

class looked_up_string
{
	FCPPT_NONCOPYABLE(
		looked_up_string
	);
public:
	looked_up_string(
		sge::x11input::focus::char_vector &&,
		sge::input::key::code
	)
	noexcept;

	looked_up_string(
		looked_up_string &&
	)
	noexcept;

	looked_up_string &
	operator=(
		looked_up_string &&
	)
	noexcept;

	~looked_up_string()
	noexcept;

	sge::x11input::focus::char_vector const &
	char_codes() const
	noexcept;

	sge::input::key::code
	key_code() const
	noexcept;
private:
	sge::x11input::focus::char_vector char_codes_;

	sge::input::key::code key_code_;
};

}
}
}

#endif
