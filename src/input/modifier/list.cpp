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


#include "list.hpp"
#include <sge/input/keyboard/key_code.hpp>
#include <boost/assign/list_of.hpp>

sge::input::modifier::container const &sge::input::modifier::list()
{
	static container mods =
		boost::assign::list_of
		(object(
				boost::assign::list_of
					(sge::input::keyboard::key_code::lshift)
					(sge::input::keyboard::key_code::rshift),
				types::shift))
		(object(
				boost::assign::list_of
					(sge::input::keyboard::key_code::lctrl)
					(sge::input::keyboard::key_code::rctrl),
				types::ctrl))
		(object(
				boost::assign::list_of
					(sge::input::keyboard::key_code::alt)
					(sge::input::keyboard::key_code::altgr),
				types::alt)).to_container(mods);
	return mods;
}
