/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../device.hpp"
#include "../check_alc_state.hpp"
#include "../openal.hpp"
#include <sge/audio/exception.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>

sge::openal::device::device(
	ALCchar const * const specifier)
:
	device_(alcOpenDevice(specifier))
{
	SGE_OPENAL_CHECK_ALC_STATE(
		device_,
		FCPPT_TEXT("alcOpenDevice failed"),
		audio::exception
	)

	SGE_ASSERT(device_);
}

ALCdevice *
sge::openal::device::aldevice()
{
	return device_;
}

sge::openal::device::~device()
{
	if (
		alcCloseDevice(device_) == AL_FALSE
		&& !std::uncaught_exception()
	)
		throw audio::exception(
			FCPPT_TEXT("error closing audio device. this means you tried to close the device before unloading all contexts and buffers")
		);
}
