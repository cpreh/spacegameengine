//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/anisotropic_mip_filter.hpp>
#include <sge/d3d9/state/convert/mag_filter.hpp>
#include <sge/d3d9/state/convert/min_filter.hpp>
#include <sge/d3d9/state/convert/normal_mip_filter.hpp>
#include <sge/d3d9/state/core/sampler/state.hpp>
#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/d3d9/state/core/sampler/filter/visitor.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>

sge::d3d9::state::core::sampler::filter::visitor::result_type
sge::d3d9::state::core::sampler::filter::visitor::operator()(
    sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_anisotropic) const
{
  return sge::d3d9::state::core::sampler::state_vector{
      sge::d3d9::state::core::sampler::state(D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC),
      sge::d3d9::state::core::sampler::state(D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC),
      sge::d3d9::state::core::sampler::state(
          D3DSAMP_MIPFILTER, sge::d3d9::state::convert::anisotropic_mip_filter(_anisotropic.mip())),
      sge::d3d9::state::core::sampler::state(D3DSAMP_MAXANISOTROPY, _anisotropic.level().get())};
}

sge::d3d9::state::core::sampler::filter::visitor::result_type
sge::d3d9::state::core::sampler::filter::visitor::operator()(
    sge::renderer::state::core::sampler::filter::normal::parameters const &_normal) const
{
  return sge::d3d9::state::core::sampler::state_vector{
      sge::d3d9::state::core::sampler::state(
          D3DSAMP_MAGFILTER, sge::d3d9::state::convert::mag_filter(_normal.mag())),
      sge::d3d9::state::core::sampler::state(
          D3DSAMP_MINFILTER, sge::d3d9::state::convert::min_filter(_normal.min())),
      sge::d3d9::state::core::sampler::state(
          D3DSAMP_MIPFILTER, sge::d3d9::state::convert::normal_mip_filter(_normal.mip())),
      sge::d3d9::state::core::sampler::state(D3DSAMP_MAXANISOTROPY, 1u)};
}
