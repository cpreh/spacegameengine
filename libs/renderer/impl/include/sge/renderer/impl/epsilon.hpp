//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_EPSILON_HPP_INCLUDED
#define SGE_RENDERER_IMPL_EPSILON_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/literal.hpp>

namespace sge::renderer::impl
{

inline constexpr sge::renderer::scalar epsilon()
{
  return fcppt::literal<sge::renderer::scalar>(
      0.001 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );
}

}

#endif
