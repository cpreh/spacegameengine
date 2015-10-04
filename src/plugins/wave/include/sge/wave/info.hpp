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


#ifndef SGE_WAVE_INFO_HPP_INCLUDED
#define SGE_WAVE_INFO_HPP_INCLUDED

#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/wave/info_fwd.hpp>
#include <fcppt/endianness/format.hpp>


namespace sge
{
namespace wave
{

class info
{
public:
	info(
		fcppt::endianness::format,
		sge::audio::channel_count,
		sge::audio::sample_rate,
		sge::audio::bits_per_sample,
		sge::audio::sample_count
	);

	fcppt::endianness::format
	endianness() const;

	sge::audio::channel_count
	channels() const;

	sge::audio::sample_rate
	sample_rate() const;

	sge::audio::bits_per_sample
	bits_per_sample() const;

	sge::audio::sample_count
	samples() const;
private:
	fcppt::endianness::format endianness_;

	sge::audio::channel_count channels_;

	sge::audio::sample_rate sample_rate_;

	sge::audio::bits_per_sample bits_per_sample_;

	sge::audio::sample_count samples_;
};

}
}

#endif
