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


#ifndef SGE_AUDIO_SOUND_BASE_HPP_INCLUDED
#define SGE_AUDIO_SOUND_BASE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/symbol.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{
namespace sound
{
/// The base class for sounds (nonpositional, positional, streaming, nonstreaming)
/**
 * This class is an interface class, you cannot instantiate it. Audio plugins
 * (OpenAL, DirectSound) must derive from this class.
 *
 * For an introduction to the sounds, see \ref audio_overview and \ref
 * audio_example and \ref audio_positional.
 */
class SGE_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(
	base
);
public:
	/// Plays a sound using the specified repeat behavior.
	/**
	 * If the sound is already playing, nothing will be changed. If the
	 * sound is paused, it will continue from where it was paused.
	 *
	 * Otherwise, it will be played from the beginning.
	 *
	 * \see sge::audio::sound::base::toggle_pause
	 */
	virtual void
	play(
		sge::audio::sound::repeat::type) = 0;

	/// Toggles between paused and unpaused
	/**
	 * If the sound is stopped, nothing happens. If the sound is paused, it
	 * will be played (same as calling play) with the last repeat mode set
	 * (default is once). If the sound is playing, it will be paused (and
	 * the repeat mode is saved).
	 */
	virtual void
	toggle_pause() = 0;

	/// Returns the momentary plating status of the sound
	/**
	 * Usually, we don't have getters for attributes, but in this case it's
	 * neccessary since the status of this variable changes without the
	 * user interfering.
	*/
	virtual play_status::type
	status() const = 0;

	/// Changes the sound's gain ("volume")
	/**
	 * The gain is a number between 0.0 and 1.0. Behavior is
	 * implementation-defined (or plugin-defined) if you pass anything out
	 * of this range.
	 */
	virtual void
	gain(
		scalar) = 0;

	/// Changes the sound's pitch
	/**
	 * The pitch is a number between 0.0 and 1.0. Behavior is
	 * implementation-defined (or plugin-defined) if you pass anything out
	 * of this range.
	 */
	virtual void
	pitch(
		scalar) = 0;

	/// Stops the sound
	/**
	 * If the sound is already stopped, nothing happens.
	 */
	virtual void
	stop() = 0;

	/// Update the sound
	/**
	 * What this does is implementation-defined. The user is, however,
	 * advised to call this regularly, especially with streaming sounds.
	 * Backends might need this to reload more data.
	 */
	virtual void
	update() = 0;

	/** \virtualdtor */
	SGE_AUDIO_SYMBOL virtual
	~base() = 0;
protected:
	/** \protectedctor */
	SGE_AUDIO_SYMBOL explicit
	base();
};
}
}
}

#endif
