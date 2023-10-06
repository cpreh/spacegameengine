//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENAL_STREAM_SOUND_HPP_INCLUDED
#define SGE_OPENAL_STREAM_SOUND_HPP_INCLUDED

#include <sge/audio/file_ref.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/multi_buffer_holder.hpp>
#include <sge/openal/source.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

namespace sge::openal
{

class stream_sound : public sge::openal::source
{
  FCPPT_NONMOVABLE(stream_sound);

public:
  stream_sound(
      fcppt::log::object_reference,
      sge::audio::sound::nonpositional_parameters const &,
      sge::audio::file_ref);

  stream_sound(
      fcppt::log::object_reference,
      sge::audio::sound::positional_parameters const &,
      sge::audio::file_ref);

  ~stream_sound() override;

  void update() override;

  void do_play() override;

private:
  fcppt::log::object_reference const log_;

  sge::audio::file_ref const audio_file_;

  sge::audio::sample_count const buffer_samples_;

  ALenum const format_;

  sge::openal::multi_buffer_holder buffers_;

  bool fill_buffer(sge::openal::buffer_id);

  struct unified_ctor
  {
  };

  template <typename Parameters>
  stream_sound(
      fcppt::log::object_reference,
      Parameters const &,
      sge::audio::file_ref,
      sge::openal::stream_sound::unified_ctor);
};

}

#endif
