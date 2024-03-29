//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/viewport/fractional_aspect.hpp>

sge::viewport::fractional_aspect::fractional_aspect(num_type const _num, denom_type const _denom)
    : num_{_num.get()}, denom_{_denom.get()}
{
}

sge::viewport::fractional_aspect::value_type sge::viewport::fractional_aspect::num() const
{
  return this->num_;
}

sge::viewport::fractional_aspect::value_type sge::viewport::fractional_aspect::denom() const
{
  return this->denom_;
}
