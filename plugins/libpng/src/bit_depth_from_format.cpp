//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/libpng/bit_depth_from_format.hpp>
#include <sge/libpng/format.hpp>
#include <fcppt/assert/unreachable.hpp>


int
sge::libpng::bit_depth_from_format(
	sge::libpng::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::libpng::format::l8:
	case sge::libpng::format::la8:
	case sge::libpng::format::srgb8:
	case sge::libpng::format::sbgr8:
	case sge::libpng::format::srgba8:
	case sge::libpng::format::sbgra8:
		return
			8; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
	}

	FCPPT_ASSERT_UNREACHABLE;
}
