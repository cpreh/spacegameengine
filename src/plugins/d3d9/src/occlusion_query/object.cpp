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
#include <sge/d3d9/devicefuncs/create_query.hpp>
#include <sge/d3d9/occlusion_query/object.hpp>
#include <sge/d3d9/queryfuncs/get_dword.hpp>
#include <sge/d3d9/queryfuncs/issue.hpp>
#include <sge/renderer/occlusion_query/blocking_wait.hpp>
#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/optional_pixel_count.hpp>
#include <sge/renderer/occlusion_query/pixel_count.hpp>
#include <fcppt/optional_bind_construct.hpp>


sge::d3d9::occlusion_query::object::object(
	IDirect3DDevice9 &_device
)
:
	sge::renderer::occlusion_query::object(),
	query_(
		sge::d3d9::devicefuncs::create_query(
			_device,
			D3DQUERYTYPE_OCCLUSION
		)
	)
{
}

sge::d3d9::occlusion_query::object::~object()
{
}

void
sge::d3d9::occlusion_query::object::begin()
{
	sge::d3d9::queryfuncs::issue(
		*query_,
		D3DISSUE_BEGIN
	);
}

void
sge::d3d9::occlusion_query::object::end()
{
	sge::d3d9::queryfuncs::issue(
		*query_,
		D3DISSUE_END
	);
}

sge::renderer::occlusion_query::optional_pixel_count
sge::d3d9::occlusion_query::object::result(
	sge::renderer::occlusion_query::blocking_wait const _block
) const
{
	return
		fcppt::optional_bind_construct(
			sge::d3d9::queryfuncs::get_dword(
				*query_,
				_block.get()
				?
					D3DGETDATA_FLUSH
				:
					0u
			),
			[](
				DWORD const _value
			)
			{
				return
					sge::renderer::occlusion_query::pixel_count(
						_value
					);
			}
		);
}
