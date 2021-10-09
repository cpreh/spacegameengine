//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/sampler/filter/need_mipmap.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>
#include <fcppt/variant/match.hpp>

bool sge::renderer::state::core::sampler::filter::need_mipmap(
    sge::renderer::state::core::sampler::filter::parameters const &_filter)
{
  return fcppt::variant::match(
      _filter.variant(),
      [](sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_parameters) {
        return _parameters.mip() !=
               sge::renderer::state::core::sampler::filter::anisotropic::mip::off;
      },
      [](sge::renderer::state::core::sampler::filter::normal::parameters const &_parameters) {
        return _parameters.mip() != sge::renderer::state::core::sampler::filter::normal::mip::off;
      });
}
