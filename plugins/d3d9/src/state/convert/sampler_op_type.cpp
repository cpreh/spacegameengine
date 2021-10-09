//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/sampler_op_type.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/color_op_fwd.hpp>

D3DTEXTURESTAGESTATETYPE
sge::d3d9::state::convert::sampler_op_type<sge::renderer::state::ffp::sampler::alpha_op>::get()
{
  return D3DTSS_ALPHAOP;
}

D3DTEXTURESTAGESTATETYPE
sge::d3d9::state::convert::sampler_op_type<sge::renderer::state::ffp::sampler::color_op>::get()
{
  return D3DTSS_COLOROP;
}
