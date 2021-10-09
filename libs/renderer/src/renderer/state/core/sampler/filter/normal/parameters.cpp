//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/sampler/filter/normal/mag.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>

sge::renderer::state::core::sampler::filter::normal::parameters::parameters(
    sge::renderer::state::core::sampler::filter::normal::mag const _mag,
    sge::renderer::state::core::sampler::filter::normal::min const _min,
    sge::renderer::state::core::sampler::filter::normal::mip const _mip)
    : mag_(_mag), min_(_min), mip_(_mip)
{
}

sge::renderer::state::core::sampler::filter::normal::mag
sge::renderer::state::core::sampler::filter::normal::parameters::mag() const
{
  return mag_;
}

sge::renderer::state::core::sampler::filter::normal::min
sge::renderer::state::core::sampler::filter::normal::parameters::min() const
{
  return min_;
}

sge::renderer::state::core::sampler::filter::normal::mip
sge::renderer::state::core::sampler::filter::normal::parameters::mip() const
{
  return mip_;
}

bool sge::renderer::state::core::sampler::filter::normal::operator==(
    sge::renderer::state::core::sampler::filter::normal::parameters const &_left,
    sge::renderer::state::core::sampler::filter::normal::parameters const &_right)
{
  return _left.mag() == _right.mag() && _left.min() == _right.min() && _left.mip() == _right.mip();
}
