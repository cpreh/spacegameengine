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


#include "../set_transform.hpp"
#include "../../convert/matrix.hpp"
#include "../../convert/matrix_mode.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/matrix/transpose.hpp>
#include <fcppt/text.hpp>

namespace
{

void
do_set(
	IDirect3DDevice9 *,
	D3DTRANSFORMSTATETYPE,
	D3DMATRIX const &
);

}

void
sge::d3d9::devicefuncs::set_transform(
	IDirect3DDevice9 *const _device,
	sge::renderer::matrix_mode::type const _mode,
	sge::renderer::matrix4 const &_matrix
)
{
	D3DMATRIX d3d_matrix(
		convert::matrix(
			fcppt::math::matrix::transpose(
				_matrix
			)
		)
	);

	D3DTRANSFORMSTATETYPE const d3d_mode(
		convert::matrix_mode(
			_mode
		)
	);

	switch(
		d3d_mode
	)
	{
	case D3DTS_TEXTURE0:
		// TODO: make a macro in this for fcppt!
		for(
			unsigned index = d3d_mode;
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
				d3d_matrix
			);

		return;
	}

	do_set(
		_device,
		d3d_mode,
		d3d_matrix
	);
}

namespace
{

void
do_set(
	IDirect3DDevice9 *const _device,
	D3DTRANSFORMSTATETYPE const _mode,
	D3DMATRIX const &_matrix
)
{
	if(
		_device->SetTransform(
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
