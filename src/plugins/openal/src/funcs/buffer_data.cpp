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
#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/funcs/buffer_data.hpp>
#include <fcppt/text.hpp>


void
sge::openal::funcs::buffer_data(
	sge::openal::buffer_id const _buffer,
	ALenum const _format,
	ALvoid const *const _data,
	ALsizei const _size,
	ALsizei const _freq
)
{
	::alBufferData(
		_buffer.get(),
		_format,
		_data,
		_size,
		_freq
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alBufferData failed"),
		sge::audio::exception
	)
}
