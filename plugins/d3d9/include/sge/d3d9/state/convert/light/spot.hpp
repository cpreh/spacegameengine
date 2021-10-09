//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_CONVERT_LIGHT_SPOT_HPP_INCLUDED
#define SGE_D3D9_STATE_CONVERT_LIGHT_SPOT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/state/ffp/lighting/light/spot_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace convert
{
namespace light
{

void spot(D3DLIGHT9 &, sge::renderer::state::ffp::lighting::light::spot const &);

}
}
}
}
}

#endif
