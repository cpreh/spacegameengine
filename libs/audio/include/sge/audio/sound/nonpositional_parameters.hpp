//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_SOUND_NONPOSITIONAL_PARAMETERS_HPP_INCLUDED
#define SGE_AUDIO_SOUND_NONPOSITIONAL_PARAMETERS_HPP_INCLUDED

#include <sge/audio/scalar.hpp>
#include <sge/audio/detail/symbol.hpp>


namespace sge
{
namespace audio
{
namespace sound
{

/// Holds all the data necessary to construct a nonpositional sound
class nonpositional_parameters
{
public:
	SGE_AUDIO_DETAIL_SYMBOL
	nonpositional_parameters();

	/// Get the gain
	/** \see sge::audio::sound::base::gain */
	[[nodiscard]]
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	gain() const;

	/// Set the gain
	/** \see sge::audio::sound::base::gain */
	SGE_AUDIO_DETAIL_SYMBOL
	nonpositional_parameters &
	gain(
		sge::audio::scalar
	);

	/// Get the pitch
	/** \see sge::audio::sound::base::pitch */
	[[nodiscard]]
	SGE_AUDIO_DETAIL_SYMBOL
	sge::audio::scalar
	pitch() const;

	/// Set the pitch
	/** \see sge::audio::sound::base::pitch */
	SGE_AUDIO_DETAIL_SYMBOL
	nonpositional_parameters &
	pitch(
		sge::audio::scalar
	);
private:
	sge::audio::scalar gain_;

	sge::audio::scalar pitch_;
};

}
}
}

#endif
