//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/exception.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/impl/is_epsilon_equal.hpp>
#include <sge/renderer/impl/projection/check_near.hpp>
#include <sge/renderer/projection/near.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>

void sge::renderer::impl::projection::check_near(sge::renderer::projection::near const _near)
{
  if (sge::renderer::impl::is_epsilon_equal(_near.get(), fcppt::literal<sge::renderer::scalar>(0)))
  {
    throw sge::renderer::exception{FCPPT_TEXT("projection: near must not be 0!")};
  }
}
