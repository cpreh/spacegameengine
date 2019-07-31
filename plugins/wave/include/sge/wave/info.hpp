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
