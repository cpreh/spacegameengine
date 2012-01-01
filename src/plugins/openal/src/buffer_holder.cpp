/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/openal/buffer_holder.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/log.hpp>
#include <sge/openal/openal.hpp>
#include <sge/audio/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/output.hpp>


sge::openal::buffer_holder::buffer_holder()
{

	::alGenBuffers(
		static_cast<
			ALsizei
		>(
			1
		),
		&buffer_
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGenBuffers failed"),
		audio::exception
	)
}

sge::openal::buffer_holder::~buffer_holder()
{
	FCPPT_LOG_DEBUG(
		openal::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Deleting a buffer")
	);


	::alDeleteBuffers(
		static_cast<
			ALsizei
		>(
			1
		),
		&buffer_
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alDeleteBuffers failed"),
		audio::exception
	)
}

ALuint
sge::openal::buffer_holder::get() const
{
	return buffer_;
}
