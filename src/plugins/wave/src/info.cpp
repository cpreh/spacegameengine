/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/wave/info.hpp>
#include <fcppt/endianness/format.hpp>


sge::wave::info::info(
	fcppt::endianness::format const _endianness,
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

fcppt::endianness::format
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
