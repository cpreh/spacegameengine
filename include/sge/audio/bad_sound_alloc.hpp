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


#ifndef SGE_AUDIO_BAD_SOUND_ALLOC_HPP_INCLUDED
#define SGE_AUDIO_BAD_SOUND_ALLOC_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace audio
{

/// Exception thrown when sound resource limits are reached.
/**
 * This exception is thrown if an audio player plugin isn't able to allocate
 * enough resources for a sound. This happens, for example, when OpenAL cannot
 * create another sound source (because the internal limit is reached).
 */
class SGE_CLASS_SYMBOL bad_sound_alloc
:
	public audio::exception
{
public:
	/// Initialize exception with an error string
	SGE_AUDIO_SYMBOL
	explicit bad_sound_alloc(
		fcppt::string const &
	);
};

}
}

#endif
