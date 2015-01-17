/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/devicefuncs/set_transform.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


namespace
{

void
do_set(
	IDirect3DDevice9 &,
	D3DTRANSFORMSTATETYPE,
	D3DMATRIX const &
);

}

void
sge::d3d9::devicefuncs::set_transform(
	IDirect3DDevice9 &_device,
	D3DTRANSFORMSTATETYPE const _mode,
	D3DMATRIX const &_matrix
)
{
	if(
		_mode
		==
		D3DTS_TEXTURE0
	)
	{
		// TODO: make a macro in this for fcppt!
		for(
			unsigned index = _mode;
			index <= D3DTS_TEXTURE7;
			++index
		)
			do_set(
				_device,
				static_cast<
					D3DTRANSFORMSTATETYPE
				>(
					index
				),
				_matrix
			);

		return;
	}

	do_set(
		_device,
		_mode,
		_matrix
	);
}

namespace
{

void
do_set(
	IDirect3DDevice9 &_device,
	D3DTRANSFORMSTATETYPE const _mode,
	D3DMATRIX const &_matrix
)
{
	if(
		_device.SetTransform(
			_mode,
			&_matrix
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetTransform() failed!")
		);
}

}
