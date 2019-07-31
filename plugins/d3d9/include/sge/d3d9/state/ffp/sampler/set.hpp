//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_FFP_SAMPLER_SET_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_SAMPLER_SET_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/sampler/object_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace sampler
{

void
set(
	IDirect3DDevice9 &,
	sge::renderer::state::ffp::sampler::const_object_ref_vector const &,
	sge::d3d9::state::ffp::sampler::object const &,
	sge::renderer::caps::texture_stages
);

}
}
}
}
}

#endif
