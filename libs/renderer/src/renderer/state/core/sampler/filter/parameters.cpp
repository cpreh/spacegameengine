//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/variant.hpp>
#include <fcppt/variant/comparison.hpp>

sge::renderer::state::core::sampler::filter::parameters::parameters(
    sge::renderer::state::core::sampler::filter::variant const &_variant)
    : variant_(_variant)
{
}

sge::renderer::state::core::sampler::filter::variant const &
sge::renderer::state::core::sampler::filter::parameters::variant() const
{
  return variant_;
}

bool sge::renderer::state::core::sampler::filter::operator==(
    sge::renderer::state::core::sampler::filter::parameters const &_left,
    sge::renderer::state::core::sampler::filter::parameters const &_right)
{
  return _left.variant() == _right.variant();
}
