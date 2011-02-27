/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../lock_planar.hpp"
#include "../../convert/rect.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>

D3DLOCKED_RECT const
sge::d3d9::texture::lock_planar(
	d3d9::d3d_texture_ptr const _texture,
	sge::renderer::stage_type const _stage,
	d3d9::texture::optional_lock_rect const &_rect,
	d3d9::lock_flags const _flags
)
{
	D3DLOCKED_RECT ret;

	RECT in_rect = {};

	if(
		_rect
	)
		in_rect =
			d3d9::convert::rect(
				_*rect
			);

	if(
		_texture->LockRect(
			_stage.get(),
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
			FCPPT_TEXT("LockRect() failed!")
		);

	return ret;
}
