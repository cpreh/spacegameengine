//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_AUDIO_BAD_SOUND_ALLOC_HPP_INCLUDED
#define SGE_AUDIO_BAD_SOUND_ALLOC_HPP_INCLUDED

#include <sge/audio/exception.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/core/detail/class_symbol.hpp>
#include <fcppt/string.hpp>

namespace sge::audio
{

/// Exception thrown when sound resource limits are reached.
/**
 * This exception is thrown if an audio player plugin isn't able to allocate
 * enough resources for a sound. This happens, for example, when OpenAL cannot
 * create another sound source (because the internal limit is reached).
 */
class SGE_CORE_DETAIL_CLASS_SYMBOL bad_sound_alloc : public sge::audio::exception
{
public:
  /// Initialize exception with an error string
  SGE_AUDIO_DETAIL_SYMBOL
  explicit bad_sound_alloc(fcppt::string &&);

  SGE_AUDIO_DETAIL_SYMBOL
  bad_sound_alloc(bad_sound_alloc &&) noexcept;

  SGE_AUDIO_DETAIL_SYMBOL
  bad_sound_alloc(bad_sound_alloc const &);

  SGE_AUDIO_DETAIL_SYMBOL
  bad_sound_alloc &operator=(bad_sound_alloc &&) noexcept;

  SGE_AUDIO_DETAIL_SYMBOL
  bad_sound_alloc &operator=(bad_sound_alloc const &);

  SGE_AUDIO_DETAIL_SYMBOL
  ~bad_sound_alloc() noexcept override;
};

}

#endif
