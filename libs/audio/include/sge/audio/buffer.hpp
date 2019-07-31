//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_AUDIO_BUFFER_HPP_INCLUDED
#define SGE_AUDIO_BUFFER_HPP_INCLUDED

#include <sge/audio/detail/symbol.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace audio
{

/// Interface class for buffers (nonstreaming sound factories)
/**
 * The buffer class is an interface class, you cannot instantiate it. Audio
 * plugins (OpenAL, DirectSound) must derive from this class and create
 * instances when a buffer is created via sge::audio::player::create_buffer.
 *
 * For a short introduction to buffers, see \ref audio_overview and
 * \ref audio_example.
 */
class SGE_CORE_DETAIL_CLASS_SYMBOL buffer
{
	FCPPT_NONCOPYABLE(
		buffer
	);
public:
	/// Create a positional sound
	/**
	 * For an introduction to positional (3D) sounds, see \ref audio_positional
	 */
	virtual
	sge::audio::sound::positional_unique_ptr
	create_positional(
		sge::audio::sound::positional_parameters const &
	) = 0;

	/// Create a nonpositional sound
	/**
	 * For an introduction to nonpositional sounds, see \ref audio_example
	 */
	virtual
	sge::audio::sound::base_unique_ptr
	create_nonpositional(
		sge::audio::sound::nonpositional_parameters const &
	) = 0;

	SGE_AUDIO_DETAIL_SYMBOL
	virtual
	~buffer();
protected:
	SGE_AUDIO_DETAIL_SYMBOL
	buffer();
};

}
}

#endif
