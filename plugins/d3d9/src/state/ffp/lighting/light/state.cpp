//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/lighting/light/state.hpp>

sge::d3d9::state::ffp::lighting::light::state::state(D3DLIGHT9 const &_light) : light_(_light) {}

D3DLIGHT9 const &sge::d3d9::state::ffp::lighting::light::state::light() const { return light_; }
