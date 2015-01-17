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


#ifndef SGE_DINPUT_MOUSE_ENUMERATOR_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_ENUMERATOR_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace dinput
{
namespace mouse
{

class enumerator
:
	public sge::dinput::device::enumerator
{
	FCPPT_NONCOPYABLE(
		enumerator
	);
public:
	enumerator();

	~enumerator();

	sge::input::mouse::axis_info_container::vector const &
	axis() const;

	sge::input::mouse::button_info_container::vector const &
	buttons() const;

	sge::dinput::mouse::axis_map const &
	axis_map() const;

	sge::dinput::mouse::button_map const &
	button_map() const;
private:
	void
	dispatch(
		DIDEVICEOBJECTINSTANCE const &
	);

	sge::input::mouse::axis_info_container::vector axis_;

	sge::input::mouse::button_info_container::vector buttons_;

	sge::dinput::mouse::axis_map axis_map_;

	sge::dinput::mouse::button_map button_map_;
};

}
}
}

#endif
