/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/optional_lock_rect.hpp>
#include <sge/d3d9/convert/lock_rect.hpp>
#include <sge/d3d9/surfacefuncs/lock_rect.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


D3DLOCKED_RECT const
sge::d3d9::surfacefuncs::lock_rect(
	IDirect3DSurface9 &_surface,
	sge::d3d9::optional_lock_rect const &_rect,
	sge::d3d9::lock_flags const _flags
)
{
	D3DLOCKED_RECT ret = {};

	RECT in_rect = {};

	if(
		_rect
	)
		in_rect =
			sge::d3d9::convert::lock_rect(
				*_rect
			);

	if(
		_surface.LockRect(
			&ret,
			_rect
			?
				&in_rect
			:
				NULL,
			_flags.get()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Surface::LockRect() failed!")
		);

	return ret;
}
