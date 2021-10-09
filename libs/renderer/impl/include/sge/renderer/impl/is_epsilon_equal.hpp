//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_IS_EPSILON_EQUAL_HPP_INCLUDED
#define SGE_RENDERER_IMPL_IS_EPSILON_EQUAL_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/impl/epsilon.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

namespace sge::renderer::impl
{

inline bool is_epsilon_equal(sge::renderer::scalar const _a, sge::renderer::scalar const _b)
{
  return std::abs(_a - _b) < sge::renderer::impl::epsilon();
}

}

#endif
