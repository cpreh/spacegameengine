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


#ifndef SGE_CEGUI_SYRINGE_HPP_INCLUDED
#define SGE_CEGUI_SYRINGE_HPP_INCLUDED

#include <sge/cegui/symbol.hpp>
#include <sge/cegui/system_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/input/cursor/button_event_fwd.hpp>
#include <sge/input/cursor/move_event_fwd.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/keyboard/char_event_fwd.hpp>
#include <sge/input/keyboard/key_event_fwd.hpp>
#include <sge/input/keyboard/key_repeat_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sge
{
namespace cegui
{
class syringe
{
FCPPT_NONCOPYABLE(
	syringe);
public:
	SGE_CEGUI_SYMBOL explicit
	syringe(
		system &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::keyboard::key_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::keyboard::key_repeat_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::keyboard::char_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::cursor::button_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::cursor::move_event const &);

	SGE_CEGUI_SYMBOL void
	inject(
		sge::input::cursor::position const &);
private:
	system &system_;
	sge::charconv::system &charconv_system_;
};
}
}

#endif
