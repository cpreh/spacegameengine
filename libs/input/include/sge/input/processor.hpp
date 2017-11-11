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


#ifndef SGE_INPUT_PROCESSOR_HPP_INCLUDED
#define SGE_INPUT_PROCESSOR_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace input
{

class SGE_CORE_DETAIL_CLASS_SYMBOL processor
{
	FCPPT_NONCOPYABLE(
		processor
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	processor();
public:
	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~processor() = 0;

	// TODO: Can we remove this?
	virtual
	sge::window::object &
	window() const = 0;

	virtual
	sge::input::cursor::container
	cursors() const = 0;

	virtual
	sge::input::focus::container
	foci() const = 0;

	virtual
	sge::input::joypad::container
	joypads() const = 0;

	virtual
	sge::input::keyboard::container
	keyboards() const = 0;

	virtual
	sge::input::mouse::container
	mice() const = 0;
};

}
}

#endif
