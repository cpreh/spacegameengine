//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_ANISOTROPIC_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_ANISOTROPIC_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/level.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters_fwd.hpp> // IWYU pragma: keep

namespace sge::renderer::state::core::sampler::filter::anisotropic
{

class parameters
{
public:
  SGE_RENDERER_DETAIL_SYMBOL
  parameters(
      sge::renderer::state::core::sampler::filter::anisotropic::mip,
      sge::renderer::state::core::sampler::filter::anisotropic::level);

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::sampler::filter::anisotropic::mip
      mip() const;

  [[nodiscard]] SGE_RENDERER_DETAIL_SYMBOL
      sge::renderer::state::core::sampler::filter::anisotropic::level
      level() const;

private:
  sge::renderer::state::core::sampler::filter::anisotropic::mip mip_;

  sge::renderer::state::core::sampler::filter::anisotropic::level level_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool operator==(
    sge::renderer::state::core::sampler::filter::anisotropic::parameters const &,
    sge::renderer::state::core::sampler::filter::anisotropic::parameters const &);

}

#endif
