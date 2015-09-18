/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CEGUI_DEFAULT_FOCUS_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_FOCUS_HPP_INCLUDED

#include <sge/cegui/syringe_fwd.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <sge/input/focus/char_event_fwd.hpp>
#include <sge/input/focus/key_event_fwd.hpp>
#include <sge/input/focus/key_repeat_event_fwd.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace cegui
{

class default_focus
{
	FCPPT_NONCOPYABLE(
		default_focus
	);
public:
	SGE_CEGUI_DETAIL_SYMBOL
	default_focus(
		sge::cegui::syringe &,
		sge::input::focus::object &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	~default_focus();
private:
	sge::cegui::syringe &syringe_;

	fcppt::signal::scoped_connection const
		key_callback_,
		key_repeat_callback_,
		char_callback_;

	void
	key_callback(
		sge::input::focus::key_event const &
	);

	void
	key_repeat_callback(
		sge::input::focus::key_repeat_event const &
	);

	void
	char_callback(
		sge::input::focus::char_event const &
	);
};

}
}

#endif
