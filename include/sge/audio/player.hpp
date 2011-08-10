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


#ifndef SGE_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_HPP_INCLUDED

#include <sge/audio/player_fwd.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/buffer_ptr.hpp>
#include <sge/audio/player_capabilities_field.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace audio
{

class SGE_CLASS_SYMBOL player
{
public:
	FCPPT_NONCOPYABLE(
		player
	);
protected:
	SGE_AUDIO_SYMBOL explicit
	player();
public:
	virtual audio::listener &
	listener() = 0;

	virtual scalar
	speed_of_sound() const = 0;

	virtual scalar
	doppler_factor() const = 0;

	virtual void
	speed_of_sound(
		scalar
	) = 0;

	virtual void
	doppler_factor(
		scalar
	) = 0;

	virtual void
	gain(
		scalar
	) = 0;

	virtual scalar
	gain() const = 0;

	virtual buffer_ptr const
	create_buffer(
		audio::file &
	) = 0;

	virtual sound::positional_ptr const
	create_positional_stream(
		audio::file_ptr,
		sound::positional_parameters const &
	) = 0;

	virtual sound::base_ptr const
	create_nonpositional_stream(
		audio::file_ptr
	) = 0;

	virtual player_capabilities_field const
	capabilities() const = 0;

	SGE_AUDIO_SYMBOL virtual ~player();
};

}
}

#endif // PLAYER_HPP
