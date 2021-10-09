//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <mizuiro/image/algorithm/uninitialized.hpp>
#include <fcppt/assert/unreachable.hpp>

mizuiro::image::algorithm::uninitialized sge::image::impl::algorithm::convert_uninitialized(
    sge::image::algorithm::uninitialized const _uninitialized)
{
  switch (_uninitialized)
  {
  case sge::image::algorithm::uninitialized::no:
    return mizuiro::image::algorithm::uninitialized::no;
  case sge::image::algorithm::uninitialized::yes:
    return mizuiro::image::algorithm::uninitialized::yes;
  }

  FCPPT_ASSERT_UNREACHABLE;
}
