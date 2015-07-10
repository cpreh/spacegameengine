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


#ifndef SGE_D3D9_STATE_CORE_DEFAULTS_HPP_INCLUDED
#define SGE_D3D9_STATE_CORE_DEFAULTS_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/core/defaults_fwd.hpp>
#include <sge/d3d9/state/core/blend/object_fwd.hpp>
#include <sge/d3d9/state/core/blend/object_unique_ptr.hpp>
#include <sge/d3d9/state/core/depth_stencil/object_fwd.hpp>
#include <sge/d3d9/state/core/depth_stencil/object_unique_ptr.hpp>
#include <sge/d3d9/state/core/rasterizer/object_fwd.hpp>
#include <sge/d3d9/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/d3d9/state/core/sampler/object_fwd.hpp>
#include <sge/d3d9/state/core/sampler/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace core
{

class defaults
{
	FCPPT_NONCOPYABLE(
		defaults
	);
public:
	explicit
	defaults(
		IDirect3DDevice9 &
	);

	~defaults();

	sge::d3d9::state::core::blend::object const &
	blend() const;

	sge::d3d9::state::core::depth_stencil::object const &
	depth_stencil() const;

	sge::d3d9::state::core::rasterizer::object const &
	rasterizer() const;

	sge::d3d9::state::core::sampler::object const &
	sampler() const;
private:
	sge::d3d9::state::core::blend::object_unique_ptr const blend_;

	sge::d3d9::state::core::depth_stencil::object_unique_ptr const depth_stencil_;

	sge::d3d9::state::core::rasterizer::object_unique_ptr const rasterizer_;

	sge::d3d9::state::core::sampler::object_unique_ptr const sampler_;
};

}
}
}
}

#endif
