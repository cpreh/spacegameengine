//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/exception.hpp>
#include <sge/renderer/impl/is_epsilon_equal.hpp>
#include <sge/renderer/impl/projection/check_near_far.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <fcppt/text.hpp>

void sge::renderer::impl::projection::check_near_far(
    sge::renderer::projection::near const _near, sge::renderer::projection::far const _far)
{
  if (sge::renderer::impl::is_epsilon_equal(_far.get(), _near.get()))
  {
    throw sge::renderer::exception{FCPPT_TEXT("projection: far may not be near!")};
  }
}
