//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/exception.hpp>
#include <sge/cg/impl/parameter/vector/element_count.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/vector/detail/check_size.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/size_type.hpp>

void sge::cg::parameter::vector::detail::check_size(
    sge::cg::parameter::object const &_parameter, fcppt::math::size_type const _size)
{
  if (sge::cg::impl::parameter::vector::element_count(_parameter) != _size)
  {
    throw sge::cg::exception{FCPPT_TEXT("Unexpected vector size!")};
  }
}
