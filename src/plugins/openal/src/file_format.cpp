/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../file_format.hpp"
#include <sge/audio/file.hpp>
#include <sge/audio/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/string.hpp>
#include <fcppt/lexical_cast.hpp>

ALenum
sge::openal::file_format(
	audio::file const &file)
{
	if (file.bits_per_sample() == static_cast<audio::sample_count>(8) && file.channels() == static_cast<audio::channel_type>(1))
		return AL_FORMAT_MONO8;
	if (file.bits_per_sample() == static_cast<audio::sample_count>(8) && file.channels() == static_cast<audio::channel_type>(2))
		return AL_FORMAT_STEREO8;
	if (file.bits_per_sample() == static_cast<audio::sample_count>(16) && file.channels() == static_cast<audio::channel_type>(1))
		return AL_FORMAT_MONO16;
	if (file.bits_per_sample() == static_cast<audio::sample_count>(16) && file.channels() == static_cast<audio::channel_type>(2))
		return AL_FORMAT_STEREO16;

	throw audio::exception(
		FCPPT_TEXT("OpenAL error: Format not supported: ")
		+ fcppt::lexical_cast<fcppt::string>(file.bits_per_sample())
		+ FCPPT_TEXT(" bps, ")
		+ fcppt::lexical_cast<fcppt::string>(file.channels())
		+ FCPPT_TEXT(" channels"));
}
