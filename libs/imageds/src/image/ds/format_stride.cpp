//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/channel16.hpp>
#include <sge/image/channel32.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/ds/format.hpp>
#include <sge/image/ds/format_stride.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::size_type
sge::image::ds::format_stride(
	sge::image::ds::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::image::ds::format::d16:
		return
			sizeof(
				sge::image::channel16
			);
	case sge::image::ds::format::d32:
	case sge::image::ds::format::d24s8:
		return
			sizeof(
				sge::image::channel32
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
