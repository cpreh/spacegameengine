#include "synth.hpp"
#include "frame.hpp"
#include <sge/raw_vector_impl.hpp>
#include <sge/log/headers.hpp>
#include <limits>
#include <limits.h>
#include <cstddef>
#include <cmath>
#include <boost/cstdint.hpp>

namespace
{
sge::mad::synth::sample_type mad_to_native(mad_fixed_t fixed)
{
	if(fixed>=MAD_F_ONE)
		return SHRT_MAX;
	if(fixed<=-MAD_F_ONE)
		return -SHRT_MAX;

	fixed=fixed>>(MAD_F_FRACBITS-15);
	return((signed short)fixed);

	/*
	if(fixed>=MAD_F_ONE)
		return SHRT_MAX;
	if(fixed<=-MAD_F_ONE)
		return -SHRT_MAX;
	
	sge::mad::synth::sample_type result = 
		static_cast<sge::mad::synth::sample_type>(
			(fixed & 0x0fffffff) >> 12);

	if (fixed & 0x80000000)
		return -result;

	return result;
	*/

	/* round */
	//static int counter = 0;
	//return std::sin((counter++) * 100) * 60000;

	/*
  fixed += (1L << (MAD_F_FRACBITS - 16));

  if (fixed >= MAD_F_ONE)
    fixed = MAD_F_ONE - 1;
  else if (fixed < -MAD_F_ONE)
    fixed = -MAD_F_ONE;

  return fixed >> (MAD_F_FRACBITS + 1 - 16);
	*/

		
	/*
	fixed=fixed>>(MAD_F_FRACBITS-15);
	return((signed short)fixed);
	*/
}
}

sge::mad::synth::synth(frame &f)
{
	mad_synth_init(&synth_);
	mad_synth_frame(&synth_,&(f.madframe()));

	for (unsigned i = static_cast<unsigned>(0); 
	     i < static_cast<unsigned>(synth_.pcm.length); 
			 ++i)
		synthed_samples.push_back(
			std::make_pair(
				mad_to_native(synth_.pcm.samples[0][i]),
				mad_to_native(synth_.pcm.samples[1][i])));
}

sge::audio::sample_count sge::mad::synth::sample_count() const
{
	return synth_.pcm.length;
}

sge::mad::synth::~synth()
{
	mad_synth_finish(&synth_);
}
