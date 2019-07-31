//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_rect.hpp>
#include <sge/d3d9/convert/lock_rect.hpp>
#include <sge/d3d9/surfacefuncs/lock_rect.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe_void.hpp>


D3DLOCKED_RECT const
sge::d3d9::surfacefuncs::lock_rect(
	IDirect3DSurface9 &_surface,
	sge::d3d9::optional_lock_rect const &_opt_rect,
	sge::d3d9::lock_flags const _flags
)
{
	D3DLOCKED_RECT ret;

	RECT in_rect;

	fcppt::optional::maybe_void(
		_opt_rect,
		[
			&in_rect
		](
			sge::renderer::lock_rect const _rect
		)
		{
			in_rect =
				sge::d3d9::convert::lock_rect(
					_rect
				);
		}
	);

	if(
		_surface.LockRect(
			&ret,
			_opt_rect.has_value()
			?
				&in_rect
			:
				NULL,
			_flags.get()
		)
		!= D3D_OK
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("Surface::LockRect() failed!")
			};

	return
		ret;
}
