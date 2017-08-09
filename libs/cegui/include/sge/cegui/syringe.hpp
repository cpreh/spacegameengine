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


#ifndef SGE_CEGUI_SYRINGE_HPP_INCLUDED
#define SGE_CEGUI_SYRINGE_HPP_INCLUDED

#include <sge/cegui/syringe_fwd.hpp>
#include <sge/cegui/system_fwd.hpp>
#include <sge/cegui/detail/symbol.hpp>
#include <sge/input/cursor/position_fwd.hpp>
#include <sge/input/cursor/event/button_fwd.hpp>
#include <sge/input/cursor/event/move_fwd.hpp>
#include <sge/input/cursor/event/scroll_fwd.hpp>
#include <sge/input/focus/event/char_fwd.hpp>
#include <sge/input/focus/event/key_fwd.hpp>
#include <sge/input/focus/event/key_repeat_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace CEGUI
{
class GUIContext;
}


namespace sge
{
namespace cegui
{

class syringe
{
	FCPPT_NONCOPYABLE(
		syringe
	);
public:
	SGE_CEGUI_DETAIL_SYMBOL
	syringe(
		fcppt::log::context &,
		sge::cegui::system &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	~syringe();

	SGE_CEGUI_DETAIL_SYMBOL
	void
	inject(
		sge::input::focus::event::key const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	void
	inject(
		sge::input::focus::event::key_repeat const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	void
	inject(
		sge::input::focus::event::char_ const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	void
	inject(
		sge::input::cursor::event::button const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	void
	inject(
		sge::input::cursor::event::move const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	void
	inject(
		sge::input::cursor::event::scroll const &
	);

	SGE_CEGUI_DETAIL_SYMBOL
	void
	inject(
		sge::input::cursor::position const &
	);
private:
	CEGUI::GUIContext &gui_context_;

	fcppt::log::object log_;
};

}
}

#endif
