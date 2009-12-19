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


#include "../source_functions.hpp"
#include "../check_state.hpp"
#include <sge/audio/exception.hpp>
#include <sge/text.hpp>

void
sge::openal::source_i(
	ALuint const source,
	ALenum const type,
	ALint const value)
{
	alSourcei(
		source,
		type,
		value
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcei failed"),
		audio::exception
	)
}

void
sge::openal::source_f(
	ALuint const source,
	ALenum const type,
	ALfloat const value)
{
	alSourcef(
		source,
		type,
		value
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source_fv(
	ALuint const source,
	ALenum const type,
	ALfloat const *const value)
{
	alSourcefv(
		source,
		type,
		value
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcefv failed"),
		audio::exception
	)
}

void
sge::openal::source_play(
	ALuint const source)
{
	alSourcePlay(source);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcePlay failed"),
		audio::exception
	)
}


