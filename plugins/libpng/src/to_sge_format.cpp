//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/to_sge_format.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::color::format
sge::libpng::to_sge_format(
	sge::libpng::format const _format
)
{
#define SGE_LIBPNG_CONVERT_CASE(\
	cur_format\
)\
	case sge::libpng::format::cur_format:\
		return \
			sge::image::color::format::cur_format

	switch(
		_format
	)
	{
		SGE_LIBPNG_CONVERT_CASE(
			l8
		);
		SGE_LIBPNG_CONVERT_CASE(
			la8
		);
		SGE_LIBPNG_CONVERT_CASE(
			srgb8
		);
		SGE_LIBPNG_CONVERT_CASE(
			sbgr8
		);
		SGE_LIBPNG_CONVERT_CASE(
			srgba8
		);
		SGE_LIBPNG_CONVERT_CASE(
			sbgra8
		);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
