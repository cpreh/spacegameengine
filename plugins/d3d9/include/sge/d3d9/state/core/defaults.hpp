//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
