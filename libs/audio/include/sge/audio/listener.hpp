//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_LISTENER_HPP_INCLUDED
#define SGE_AUDIO_LISTENER_HPP_INCLUDED

#include <sge/audio/listener_fwd.hpp>
#include <sge/audio/vector_fwd.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/direction/object_fwd.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace audio
{

/// The player's listener
/**
 * The listener class is an interface class, you cannot instantiate it. Audio
 * plugins (OpenAL, DirectSound) must derive from this class and create
 * one listener instance per player instance. It's then accessible via the
 * sge::audio::player::listener function.
 *
 * For an introduction to the listener, see \ref audio_positional.
 */
class SGE_CORE_DETAIL_CLASS_SYMBOL listener
{
	FCPPT_NONMOVABLE(
		listener
	);
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	listener();
public:
	/// Set the position
	virtual
	void
	position(
		sge::audio::vector const &
	) = 0;

	/// Set the linear velocity
	virtual
	void
	linear_velocity(
		sge::audio::vector const &
	) = 0;

	/// Set the direction
	/**
	 * \note
	 * The direction object might or might not check if it's
	 * actually "correct" in the sense that the vectors are linearly
	 * independent and normalized. Some plugins don't even need linearly
	 * independent/normalized vectors, so they won't correct or check this
	 * either. Be careful.
	 */
	virtual
	void
	direction(
		sge::audio::direction::object const &
	) = 0;

	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~listener();
};

}
}

#endif
