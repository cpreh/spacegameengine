//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/lock_box.hpp>
#include <sge/renderer/lock_box.hpp>
#include <fcppt/cast/size.hpp>


D3DBOX
sge::d3d9::convert::lock_box(
	sge::renderer::lock_box const &_box
)
{
	return
		D3DBOX{
			fcppt::cast::size<
				UINT
			>(
				_box.left()
			),
			fcppt::cast::size<
				UINT
			>(
				_box.top()
			),
			fcppt::cast::size<
				UINT
			>(
				_box.right()
			),
			fcppt::cast::size<
				UINT
			>(
				_box.bottom()
			),
			fcppt::cast::size<
				UINT
			>(
				_box.front()
			),
			fcppt::cast::size<
				UINT
			>(
				_box.back()
			)
		};
}
