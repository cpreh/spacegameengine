//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_FFP_LIGHTING_MATERIAL_MAKE_STATES_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_LIGHTING_MATERIAL_MAKE_STATES_HPP_INCLUDED

#include <sge/d3d9/state/ffp/lighting/material/state_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace lighting
{
namespace material
{

sge::d3d9::state::ffp::lighting::material::state const
make_states(
	sge::renderer::state::ffp::lighting::material::parameters const &
);

}
}
}
}
}
}

#endif
