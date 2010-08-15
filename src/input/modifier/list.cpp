/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/input/key_code.hpp>
#include <boost/assign/list_of.hpp>

sge::input::modifier::container const &sge::input::modifier::list()
{
	static container mods =
		boost::assign::list_of
		(object(
				boost::assign::list_of
					(sge::input::kc::key_lshift)
					(sge::input::kc::key_rshift),
				types::shift))
		(object(
				boost::assign::list_of
					(sge::input::kc::key_lctrl)
					(sge::input::kc::key_rctrl),
				types::ctrl))
		(object(
				boost::assign::list_of
					(sge::input::kc::key_alt)
					(sge::input::kc::key_altgr),
				types::alt)).to_container(mods);
	return mods;
}
