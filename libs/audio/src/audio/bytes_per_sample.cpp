//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/bytes_per_sample.hpp>
#include <sge/audio/raw_data.hpp>
#include <sge/audio/sample_count.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sge::audio::sample_count
sge::audio::bytes_per_sample(
	sge::audio::bits_per_sample const _bits
)
{
	return
		_bits.get()
		/
		fcppt::cast::size<
			sge::audio::sample_count
		>(
			fcppt::cast::to_unsigned(
				std::numeric_limits<
					sge::audio::raw_data
				>::digits
			)
		);
}
