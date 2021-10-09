//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/sampler_arg.hpp>
#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <fcppt/assert/unreachable.hpp>

DWORD
sge::d3d9::state::convert::sampler_arg(sge::renderer::state::ffp::sampler::arg const _arg)
{
  switch (_arg)
  {
  case sge::renderer::state::ffp::sampler::arg::constant:
    return D3DTA_CONSTANT;
  case sge::renderer::state::ffp::sampler::arg::previous:
    return D3DTA_CURRENT;
    //		return D3DTA_SPECULAR;
    //		return D3DTA_TEMP;
  case sge::renderer::state::ffp::sampler::arg::texture:
    return D3DTA_TEXTURE;
  case sge::renderer::state::ffp::sampler::arg::vertex_color:
    // TODO: Is this correct?
    return D3DTA_DIFFUSE;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
