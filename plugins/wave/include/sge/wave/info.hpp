//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WAVE_INFO_HPP_INCLUDED
#define SGE_WAVE_INFO_HPP_INCLUDED

#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/wave/info_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <bit>
#include <fcppt/config/external_end.hpp>

namespace sge::wave
{

class info
{
public:
  info(
      std::endian,
      sge::audio::channel_count,
      sge::audio::sample_rate,
      sge::audio::bits_per_sample,
      sge::audio::sample_count);

  [[nodiscard]] std::endian endianness() const;

  [[nodiscard]] sge::audio::channel_count channels() const;

  [[nodiscard]] sge::audio::sample_rate sample_rate() const;

  [[nodiscard]] sge::audio::bits_per_sample bits_per_sample() const;

  [[nodiscard]] sge::audio::sample_count samples() const;

private:
  std::endian endianness_;

  sge::audio::channel_count channels_;

  sge::audio::sample_rate sample_rate_;

  sge::audio::bits_per_sample bits_per_sample_;

  sge::audio::sample_count samples_;
};

}

#endif
