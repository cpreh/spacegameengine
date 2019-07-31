//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/pixel_rect.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <fcppt/cast/size.hpp>


RECT
sge::d3d9::convert::pixel_rect(
	sge::renderer::pixel_rect const &_rect
)
{
	return
		RECT{
			fcppt::cast::size<
				LONG
			>(
				_rect.left()
			),
			fcppt::cast::size<
				LONG
			>(
				_rect.top()
			),
			fcppt::cast::size<
				LONG
			>(
				_rect.right()
			),
			fcppt::cast::size<
				LONG
			>(
				_rect.bottom()
			)
		};
}
