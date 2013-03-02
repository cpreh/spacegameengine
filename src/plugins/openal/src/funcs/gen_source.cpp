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


#include <sge/audio/bad_sound_alloc.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/openal.hpp>
#include <sge/openal/funcs/gen_source.hpp>
#include <fcppt/text.hpp>


ALuint
sge::openal::funcs::gen_source()
{
	ALuint result;

	::alGenSources(
		static_cast<
			ALsizei
		>(
			1
		),
		&result
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGenSources failed"),
		sge::audio::bad_sound_alloc
	)

	return result;
}
