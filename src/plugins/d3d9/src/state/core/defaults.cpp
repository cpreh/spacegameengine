/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/state/core/defaults.hpp>
#include <sge/d3d9/state/core/blend/create_default.hpp>
#include <sge/d3d9/state/core/blend/object.hpp>
#include <sge/d3d9/state/core/depth_stencil/create_default.hpp>
#include <sge/d3d9/state/core/depth_stencil/object.hpp>
#include <sge/d3d9/state/core/rasterizer/create_default.hpp>
#include <sge/d3d9/state/core/rasterizer/object.hpp>
#include <sge/d3d9/state/core/sampler/create_default.hpp>
#include <sge/d3d9/state/core/sampler/object.hpp>


sge::d3d9::state::core::defaults::defaults(
	IDirect3DDevice9 &_device
)
:
	blend_(
		sge::d3d9::state::core::blend::create_default(
			_device
		)
	),
	depth_stencil_(
		sge::d3d9::state::core::depth_stencil::create_default(
			_device
		)
	),
	rasterizer_(
		sge::d3d9::state::core::rasterizer::create_default(
			_device
		)
	),
	sampler_(
		sge::d3d9::state::core::sampler::create_default(
			_device
		)
	)
{
}

sge::d3d9::state::core::defaults::~defaults()
{
}

sge::d3d9::state::core::blend::object const &
sge::d3d9::state::core::defaults::blend() const
{
	return *blend_;
}

sge::d3d9::state::core::depth_stencil::object const &
sge::d3d9::state::core::defaults::depth_stencil() const
{
	return *depth_stencil_;
}

sge::d3d9::state::core::rasterizer::object const &
sge::d3d9::state::core::defaults::rasterizer() const
{
	return *rasterizer_;
}

sge::d3d9::state::core::sampler::object const &
sge::d3d9::state::core::defaults::sampler() const
{
	return *sampler_;
}
