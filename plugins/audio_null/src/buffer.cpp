//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/positional.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/audio_null/buffer.hpp>
#include <sge/audio_null/positional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::audio_null::buffer::buffer() = default;

sge::audio_null::buffer::~buffer() = default;

sge::audio::sound::positional_unique_ptr
sge::audio_null::buffer::create_positional(sge::audio::sound::positional_parameters const &)
{
  return fcppt::unique_ptr_to_base<sge::audio::sound::positional>(
      fcppt::make_unique_ptr<sge::audio_null::positional>());
}

sge::audio::sound::base_unique_ptr
sge::audio_null::buffer::create_nonpositional(sge::audio::sound::nonpositional_parameters const &)
{
  return fcppt::unique_ptr_to_base<sge::audio::sound::base>(
      fcppt::make_unique_ptr<sge::audio_null::positional>());
}
