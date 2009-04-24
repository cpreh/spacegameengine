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
#include "../buffer.hpp"
#include "../error.hpp"
#include <sge/audio/file.hpp>

sge::openal::buffer::buffer(audio::file &file_)
:
	file_(file_),
	refcount_(static_cast<unsigned>(1))
{
	alGenBuffers(static_cast<ALsizei>(1),&buffer_);
	SGE_OPENAL_ERROR_CHECK
}

ALuint
sge::openal::buffer::albuffer() const
{
	return buffer_;
}

sge::audio::file &sge::openal::buffer::file()
{
	return file_;
}

sge::audio::file const &sge::openal::buffer::file() const
{
	return file_;
}

void sge::openal::buffer::add_instance()
{
	refcount_++;
}	

bool sge::openal::buffer::remove_instance()
{
	if (--refcount_ != static_cast<unsigned>(0))
		return false;

	alDeleteBuffers(static_cast<ALsizei>(1),&buffer_);
	SGE_OPENAL_ERROR_CHECK
	return true;
}
