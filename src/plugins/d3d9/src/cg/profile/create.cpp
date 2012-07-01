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


#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/d3d9/cg/profile/create.hpp>
#include <sge/d3d9/cg/profile/pixel.hpp>
#include <sge/d3d9/cg/profile/vertex.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::cg::profile::object const
sge::d3d9::cg::profile::create(
	IDirect3DDevice9 &_device,
	sge::cg::profile::shader_type::type const _type
)
{
	sge::d3d9::cg::scoped_device const context(
		_device
	);

	switch(
		_type
	)
	{
	case sge::cg::profile::shader_type::vertex:
		return
			sge::d3d9::cg::profile::vertex(
				context
			);
	case sge::cg::profile::shader_type::pixel:
		return
			sge::d3d9::cg::profile::pixel(
				context
			);
	case sge::cg::profile::shader_type::geometry:
		throw sge::renderer::unsupported(
			FCPPT_TEXT("D3D9 Cg geometry shader"),
			FCPPT_TEXT("D3D10"),
			FCPPT_TEXT("")
		);
	}

	FCPPT_ASSERT_UNREACHABLE;
}

