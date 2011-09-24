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


#ifndef SGE_INPUT_JOYPAD_DEVICE_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_DEVICE_HPP_INCLUDED

#include <sge/input/joypad/device_fwd.hpp>
#include <sge/input/joypad/button_callback.hpp>
#include <sge/input/joypad/button_info_container_fwd.hpp>
#include <sge/input/joypad/axis_callback.hpp>
#include <sge/input/joypad/axis_info_container_fwd.hpp>
#include <sge/input/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace input
{
namespace joypad
{

class SGE_CLASS_SYMBOL device
{
	FCPPT_NONCOPYABLE(
		device
	);
protected:
	SGE_INPUT_SYMBOL
	device();
public:
	SGE_INPUT_SYMBOL
	virtual ~device() = 0;

	virtual fcppt::signal::auto_connection
	button_callback(
		joypad::button_callback const &
	) = 0;

	virtual fcppt::signal::auto_connection
	axis_callback(
		joypad::axis_callback const &
	) = 0;

	virtual input::joypad::button_info_container const
	buttons() const = 0;

	virtual input::joypad::axis_info_container const
	axis() const = 0;
};

}
}
}

#endif
