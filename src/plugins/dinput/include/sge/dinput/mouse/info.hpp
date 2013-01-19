/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_DINPUT_MOUSE_INFO_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_INFO_HPP_INCLUDED

#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/dinput/mouse/info_fwd.hpp>
#include <sge/input/mouse/info.hpp>


namespace sge
{
namespace dinput
{
namespace mouse
{

class info
{
public:
	info(
		sge::input::mouse::info const &,
		sge::dinput::mouse::axis_map const &,
		sge::dinput::mouse::button_map const &
	);

	sge::input::mouse::info const &
	input_info() const;

	sge::dinput::mouse::axis_map const &
	axis_map() const;

	sge::dinput::mouse::button_map const &
	button_map() const;
private:
	sge::input::mouse::info input_info_;

	sge::dinput::mouse::axis_map axis_map_;

	sge::dinput::mouse::button_map button_map_;
};

}
}
}

#endif
