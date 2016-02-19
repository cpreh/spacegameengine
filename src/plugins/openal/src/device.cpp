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


#include <sge/openal/alc.hpp>
#include <sge/openal/device.hpp>
#include <sge/openal/funcs/alc_close_device.hpp>
#include <sge/openal/funcs/alc_open_device.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error_message.hpp>


sge::openal::device::device(
	ALCchar const *const _specifier
)
:
	device_(
		sge::openal::funcs::alc_open_device(
			_specifier
		)
	)
{
}

ALCdevice &
sge::openal::device::aldevice()
{
	return
		*device_;
}

sge::openal::device::~device()
{
	FCPPT_ASSERT_ERROR_MESSAGE(
		sge::openal::funcs::alc_close_device(
			this->aldevice()
		),
		FCPPT_TEXT("Error closing audio device. This means you tried to close the device before unloading all contexts and buffers.")
	);
}
