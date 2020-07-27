//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_PLAYER_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_HPP_INCLUDED

#include <sge/audio/buffer_unique_ptr.hpp>
#include <sge/audio/file_fwd.hpp>
#include <sge/audio/file_ref.hpp>
#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/nonmovable.hpp>


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
class SGE_CORE_DETAIL_CLASS_SYMBOL player
{
	FCPPT_NONMOVABLE(
		player
	);
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	player();
public:
	[[nodiscard]]
	virtual
	sge::audio::listener &
	listener() = 0;

	/// Set the speed of sound
	/**
	 * The default is 343, the speed of sound in dry air, 20 degrees
	 * celsius, normal pressure.
	 *
	 * This is used in Doppler calculations. For an introduction to the
	 * Doppler effect, see \ref audio_positional.
	 */
	virtual
	void
	speed_of_sound(
		sge::audio::scalar
	) = 0;

	/// Set the doppler factor
	/**
	 * The default is 1.0. For an introduction to the Doppler effect, see \ref audio_positional.
	 */
	virtual
	void
	doppler_factor(
		sge::audio::scalar
	) = 0;

	/// Set the global gain (volume)
	/**
	 * The default is 1.0. This will (immediately) affect all sources
	 * created by this player.
	 */
	virtual
	void
	gain(
		sge::audio::scalar
	) = 0;

	/// Create a buffer from a file
	[[nodiscard]]
	virtual
	sge::audio::buffer_unique_ptr
	create_buffer(
		sge::audio::file & // NOLINT(google-runtime-references)
	) = 0; // NOLINT(google-runtime-references)

	/// Create a positional stream from a file
	[[nodiscard]]
	virtual
	sge::audio::sound::positional_unique_ptr
	create_positional_stream(
		sge::audio::file_ref,
		sge::audio::sound::positional_parameters const &
	) = 0;

	/// Create a nonpositional stream from a file
	[[nodiscard]]
	virtual
	sge::audio::sound::base_unique_ptr
	create_nonpositional_stream(
		sge::audio::file_ref,
		sge::audio::sound::nonpositional_parameters const &
	) = 0;

	[[nodiscard]]
	virtual
	bool
	is_null() const = 0;

	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~player();
};

}
}

#endif
