//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/wave/info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <bit>
#include <fcppt/config/external_end.hpp>


sge::wave::info::info(
	std::endian const _endianness,
	sge::audio::channel_count const _channels,
	sge::audio::sample_rate const _sample_rate,
	sge::audio::bits_per_sample const _bits_per_sample,
	sge::audio::sample_count const _samples
)
:
	endianness_{
		_endianness
	},
	channels_{
		_channels
	},
	sample_rate_{
		_sample_rate
	},
	bits_per_sample_{
		_bits_per_sample
	},
	samples_{
		_samples
	}
{
}

std::endian
sge::wave::info::endianness() const
{
	return
		endianness_;
}

sge::audio::channel_count
sge::wave::info::channels() const
{
	return
		channels_;
}

sge::audio::sample_rate
sge::wave::info::sample_rate() const
{
	return
		sample_rate_;
}

sge::audio::bits_per_sample
sge::wave::info::bits_per_sample() const
{
	return
		bits_per_sample_;
}

sge::audio::sample_count
sge::wave::info::samples() const
{
	return
		samples_;
}
