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


#ifndef SGE_WLINPUT_FOCUS_DATA_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_DATA_HPP_INCLUDED

#include <sge/input/focus/char_signal.hpp>
#include <sge/input/focus/in_signal.hpp>
#include <sge/input/focus/key_repeat_signal.hpp>
#include <sge/input/focus/key_signal.hpp>
#include <sge/input/focus/out_signal.hpp>
#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/optional_keymap.hpp>
#include <sge/wlinput/focus/optional_state.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

struct data
{
	FCPPT_NONCOPYABLE(
		data
	);

	data(
		sge::wlinput::xkb_context const &,
		awl::backends::wayland::window::object const &
	);

	~data();

	sge::wlinput::xkb_context const &xkb_context_;

	awl::backends::wayland::window::object const &window_;

	bool entered_;

	sge::wlinput::focus::optional_keymap xkb_keymap_;

	sge::wlinput::focus::optional_state xkb_state_;

	sge::input::focus::char_signal char_signal_;

	sge::input::focus::key_signal key_signal_;

	sge::input::focus::key_repeat_signal key_repeat_signal_;

	sge::input::focus::in_signal in_signal_;

	sge::input::focus::out_signal out_signal_;
};

}
}
}

#endif
