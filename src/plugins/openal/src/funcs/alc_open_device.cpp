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


#include <sge/audio/exception.hpp>
#include <sge/openal/alc.hpp>
#include <sge/openal/check_alc_state.hpp>
#include <sge/openal/funcs/alc_open_device.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/post.hpp>


ALCdevice *
sge::openal::funcs::alc_open_device(
	ALCchar const *const _specifier
)
{

	ALCdevice *const result(
		::alcOpenDevice(
			_specifier
		)
	);

	SGE_OPENAL_CHECK_ALC_STATE(
		*result,
		FCPPT_TEXT("alcOpenDevice failed"),
		sge::audio::exception
	)

	FCPPT_ASSERT_POST(
		result != nullptr,
		sge::audio::exception
	);

	return result;
}
