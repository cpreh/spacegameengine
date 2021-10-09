//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/core/sampler/address/mode_s.hpp>
#include <sge/renderer/state/core/sampler/address/mode_t.hpp>
#include <sge/renderer/state/core/sampler/address/mode_u.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wshadow)

sge::renderer::state::core::sampler::address::parameters::parameters(
    sge::renderer::state::core::sampler::address::mode_s const _mode_s,
    sge::renderer::state::core::sampler::address::mode_t const _mode_t,
    sge::renderer::state::core::sampler::address::mode_u const _mode_u)
    : mode_s_(_mode_s), mode_t_(_mode_t), mode_u_(_mode_u)
{
}

FCPPT_PP_POP_WARNING

sge::renderer::state::core::sampler::address::mode_s
sge::renderer::state::core::sampler::address::parameters::mode_s() const
{
  return mode_s_;
}

sge::renderer::state::core::sampler::address::mode_t
sge::renderer::state::core::sampler::address::parameters::mode_t() const
{
  return mode_t_;
}

sge::renderer::state::core::sampler::address::mode_u
sge::renderer::state::core::sampler::address::parameters::mode_u() const
{
  return mode_u_;
}

bool sge::renderer::state::core::sampler::address::operator==(
    sge::renderer::state::core::sampler::address::parameters const &_left,
    sge::renderer::state::core::sampler::address::parameters const &_right)
{
  return _left.mode_s() == _right.mode_s() && _left.mode_t() == _right.mode_t() &&
         _left.mode_u() == _right.mode_u();
}
