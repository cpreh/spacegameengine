//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_COMPARE_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COMPARE_IMPL_HPP_INCLUDED

#include <sge/image/algorithm/compare.hpp>
#include <sge/image/impl/algorithm/compare_visitor.hpp>
#include <sge/image/view/const_object.hpp>
#include <fcppt/variant/apply.hpp>

template <typename Tag>
bool sge::image::algorithm::compare(
    sge::image::view::const_object<Tag> const &_src1,
    sge::image::view::const_object<Tag> const &_src2)
{
  return fcppt::variant::apply(
      sge::image::impl::algorithm::compare_visitor(), _src1.get(), _src2.get());
}

#endif
