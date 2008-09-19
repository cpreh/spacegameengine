#include "synth.hpp"
#include "frame.hpp"
#include <sge/raw_vector_impl.hpp>
#include <sge/log/headers.hpp>
#include <limits>
#include <boost/cstdint.hpp>

namespace
{
typedef unsigned short pcm_length_type;

boost::int16_t mad_fixed_to_target(mad_fixed_t const fixed)
{
	if (fixed >= MAD_F_ONE)
		return std::numeric_limits<boost::uint16_t>::max();
	
	if (fixed <= -MAD_F_ONE)
		return std::numeric_limits<boost::uint16_t>::min();
	
	return static_cast<signed short>(fixed >> (MAD_F_FRACBITS-15));
}
}

sge::mad::synth::synth()
{
	mad_synth_init(&synth_);
}

void sge::mad::synth::synthesize(
	frame &f,
	audio::raw_array_type &dest,
	audio::channel_type const channels)
{
	mad_synth_frame(&synth_,&(f.madframe()));

	dest.resize(
		static_cast<audio::raw_array_type::size_type>(
			synth_.pcm.length*channels));

	audio::raw_array_type::iterator ptr = dest.begin();
	for(pcm_length_type i = static_cast<pcm_length_type>(0);
		  i < synth_.pcm.length;
		  i++)
	{
		boost::int16_t sample = mad_fixed_to_target(synth_.pcm.samples[0][i]);

		// Left channel
		*(ptr++) = static_cast<audio::raw_array_type::value_type>(sample >> 8);
		*(ptr++) = static_cast<audio::raw_array_type::value_type>(sample & 0xff);

		if (channels == static_cast<sge::audio::channel_type>(2))
		{
			if (f.channels() == static_cast<sge::audio::channel_type>(2))
				sample = mad_fixed_to_target(synth_.pcm.samples[1][i]);

			*(ptr++) = static_cast<audio::raw_array_type::value_type>(sample >> 8);
			*(ptr++) = static_cast<audio::raw_array_type::value_type>(sample & 0xff);
		}
	}
}

sge::mad::synth::~synth()
{
	mad_synth_finish(&synth_);
}
