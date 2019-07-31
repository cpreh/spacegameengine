//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_SOUND_BASE_HPP_INCLUDED
#define SGE_AUDIO_SOUND_BASE_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/sound/play_status_fwd.hpp>
#include <sge/audio/sound/repeat_fwd.hpp>
#include <sge/core/detail/class_symbol.hpp>
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
class SGE_CORE_DETAIL_CLASS_SYMBOL base
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
	virtual
	void
	play(
		sge::audio::sound::repeat
	) = 0;

	/// Toggles between paused and unpaused
	/**
	 * If the sound is stopped, nothing happens. If the sound is paused, it
	 * will be played (same as calling play) with the last repeat mode set
	 * (default is once). If the sound is playing, it will be paused (and
	 * the repeat mode is saved).
	 */
	virtual
	void
	toggle_pause() = 0;

	/// Returns the momentary plating status of the sound
	/**
	 * Usually, we don't have getters for attributes, but in this case it's
	 * neccessary since the status of this variable changes without the
	 * user interfering.
	*/
	virtual
	sge::audio::sound::play_status
	status() const = 0;

	/// Changes the sound's gain ("volume")
	/**
	 * The gain is a number between 0.0 and 1.0. Behavior is
	 * implementation-defined (or plugin-defined) if you pass anything out
	 * of this range.
	 */
	virtual
	void
	gain(
		sge::audio::scalar
	) = 0;

	/// Changes the sound's pitch
	/**
	 * The pitch is a number between 0.0 and 1.0. Behavior is
	 * implementation-defined (or plugin-defined) if you pass anything out
	 * of this range.
	 */
	virtual
	void
	pitch(
		sge::audio::scalar
	) = 0;

	/// Stops the sound
	/**
	 * If the sound is already stopped, nothing happens.
	 */
	virtual
	void
	stop() = 0;

	/// Update the sound
	/**
	 * What this does is implementation-defined. The user is, however,
	 * advised to call this regularly, especially with streaming sounds.
	 * Backends might need this to reload more data.
	 */
	virtual
	void
	update() = 0;

	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~base();
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	base();
};

}
}
}

#endif
