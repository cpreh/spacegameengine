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


#ifndef SGE_INPUT_MOUSE_INFO_HPP_INCLUDED
#define SGE_INPUT_MOUSE_INFO_HPP_INCLUDED

#include <sge/input/symbol.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/info_fwd.hpp>


namespace sge
{
namespace input
{
namespace mouse
{

class info
{
public:
	SGE_INPUT_SYMBOL
	info(
		input::mouse::axis_info_container const &,
		input::mouse::button_info_container const &,
		input::info::name const &
	);

	SGE_INPUT_SYMBOL
	input::mouse::axis_info_container const &
	axis() const;

	SGE_INPUT_SYMBOL
	input::mouse::button_info_container const &
	buttons() const;

	SGE_INPUT_SYMBOL
	input::info::name const &
	name() const;
private:
	input::mouse::axis_info_container axis_;

	input::mouse::button_info_container buttons_;

	input::info::name name_;
};

}
}
}

#endif
