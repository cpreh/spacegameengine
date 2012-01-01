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


#ifndef SGE_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/buffer_ptr.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/file_ptr.hpp>
#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/player_capabilities_field.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/audio/sound/base_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{

/// The "main" class for outputting audio
/**
 * The player class is an interface class, you cannot instantiate it. Audio
 * plugins (OpenAL, DirectSound) must derive from this class.
 *
 * For an introduction to the player, see \ref audio_overview and \ref audio_example.
 */
class SGE_CLASS_SYMBOL player
{
public:
	FCPPT_NONCOPYABLE(
		player
	);
protected:
	/** \protectedctor */
	SGE_AUDIO_SYMBOL explicit
	player();
public:
	/// The listener object
	virtual audio::listener &
	listener() = 0;

	/// Set the speed of sound
	/**
	 * The default is 343, the speed of sound in dry air, 20 degrees
	 * celsius, normal pressure.
	 *
	 * This is used in Doppler calculations. For an introduction to the
	 * Doppler effect, see \ref audio_positional.
	 */
	virtual void
	speed_of_sound(
		audio::scalar
	) = 0;

	/// Set the doppler factor
	/**
	 * The default is 1.0. For an introduction to the Doppler effect, see \ref audio_positional.
	 */
	virtual void
	doppler_factor(
		audio::scalar
	) = 0;

	/// Set the global gain (volume)
	/**
	 * The default is 1.0. This will (immediately) affect all sources
	 * created by this player.
	 */
	virtual void
	gain(
		audio::scalar
	) = 0;

	/// Create a buffer from a file
	virtual audio::buffer_ptr const
	create_buffer(
		audio::file &
	) = 0;

	/// Create a positional stream from a file
	virtual sound::positional_ptr const
	create_positional_stream(
		audio::file_ptr,
		sound::positional_parameters const &
	) = 0;

	/// Create a nonpositional stream from a file
	virtual sound::base_ptr const
	create_nonpositional_stream(
		audio::file_ptr,
		sound::nonpositional_parameters const &
	) = 0;

	/// What capabilities this player has. Is used in sge::systems to select a player.
	virtual audio::player_capabilities_field const
	capabilities() const = 0;

	/** \virtualdtor */
	SGE_AUDIO_SYMBOL
	virtual ~player() = 0;
};

}
}

#endif // PLAYER_HPP
