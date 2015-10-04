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


#include <sge/audio/exception.hpp>
#include <sge/openal/alc.hpp>
#include <sge/openal/check_alc_state.hpp>
#include <sge/openal/funcs/alc_create_context.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


ALCcontext *
sge::openal::funcs::alc_create_context(
	ALCdevice &_device
)
{
	std::array<
		ALCint,
		1u
	> const attributes = {{
		0
	}};

	ALCcontext *const result(
		::alcCreateContext(
			&_device,
			attributes.data()
		)
	);

	SGE_OPENAL_CHECK_ALC_STATE(
		_device,
		FCPPT_TEXT("alcCreateContext failed"),
		sge::audio::exception
	)

	FCPPT_ASSERT_POST(
		result,
		sge::audio::exception
	);

	return
		result;
}
