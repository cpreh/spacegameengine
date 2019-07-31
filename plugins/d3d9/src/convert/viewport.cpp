//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/viewport.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/cast/size.hpp>


D3DVIEWPORT9
sge::d3d9::convert::viewport(
	sge::renderer::target::viewport const &_viewport
)
{
	sge::renderer::pixel_rect const rect(
		_viewport.get()
	);

	return
		D3DVIEWPORT9{
			fcppt::cast::size<
				DWORD
			>(
				rect.left()
			),
			fcppt::cast::size<
				DWORD
			>(
				rect.top()
			),
			fcppt::cast::size<
				DWORD
			>(
				rect.size().w()
			),
			fcppt::cast::size<
				DWORD
			>(
				rect.size().h()
			),
			0.f,
			1.f
		};
}
