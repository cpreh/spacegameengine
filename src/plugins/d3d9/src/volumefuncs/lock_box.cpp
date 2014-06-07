/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/optional_lock_box.hpp>
#include <sge/d3d9/convert/lock_box.hpp>
#include <sge/d3d9/volumefuncs/lock_box.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


D3DLOCKED_BOX const
sge::d3d9::volumefuncs::lock_box(
	IDirect3DVolume9 &_volume,
	sge::d3d9::optional_lock_box const &_box,
	sge::d3d9::lock_flags const _flags
)
{
	D3DLOCKED_BOX ret = {};

	D3DBOX in_box  = {};

	if(
		_box
	)
		in_box =
			sge::d3d9::convert::lock_box(
				*_box
			);

	if(
		_volume.LockBox(
			&ret,
			_box
			?
				&in_box
			:
				nullptr
			,
			_flags.get()
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Volume::LockBox() failed!")
		);

	return ret;
}
