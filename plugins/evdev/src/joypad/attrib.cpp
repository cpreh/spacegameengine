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


#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/add_parameters.hpp>
#include <sge/evdev/joypad/attrib.hpp>
#include <fcppt/container/find_opt.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


void
sge::evdev::joypad::attrib(
	fcppt::log::object &_log,
	sge::evdev::joypad::add_parameters const &_parameters,
	boost::filesystem::path const &_path
)
{
	if(
		fcppt::container::find_opt(
			_parameters.map(),
			_path
		).has_value()
	)
		return;

	sge::evdev::joypad::add(
		_log,
		_parameters,
		_path
	);
}
