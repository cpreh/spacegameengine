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


#ifndef SGE_EVDEV_JOYPAD_FF_UPLOADED_EFFECT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_UPLOADED_EFFECT_HPP_INCLUDED

#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/joypad/ff/id.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace ff
{

class uploaded_effect
{
	FCPPT_NONCOPYABLE(
		uploaded_effect
	);
public:
	uploaded_effect(
		sge::evdev::device::fd const &,
		ff_effect
	);

	~uploaded_effect();

	sge::evdev::joypad::ff::id
	id() const;
private:
	sge::evdev::device::fd const &fd_;

	ff_effect effect_;
};

}
}
}
}

#endif
