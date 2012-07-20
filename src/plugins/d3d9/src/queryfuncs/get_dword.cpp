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
#include <sge/d3d9/queryfuncs/get_data.hpp>
#include <sge/d3d9/queryfuncs/get_dword.hpp>
#include <sge/d3d9/queryfuncs/optional_dword.hpp>
#include <fcppt/assert/pre.hpp>


sge::d3d9::queryfuncs::optional_dword const
sge::d3d9::queryfuncs::get_dword(
	IDirect3DQuery9 &_query,
	DWORD const _flags
)
{
	DWORD result;

	DWORD const size(
		sizeof(
			DWORD
		)
	);

	FCPPT_ASSERT_PRE(
		_query.GetDataSize()
		==
		size
	);

	return
		sge::d3d9::queryfuncs::get_data(
			_query,
			&result,
			size,
			_flags
		)
		?
			sge::d3d9::queryfuncs::optional_dword(
				result
			)
		:
			sge::d3d9::queryfuncs::optional_dword()
		;
}
