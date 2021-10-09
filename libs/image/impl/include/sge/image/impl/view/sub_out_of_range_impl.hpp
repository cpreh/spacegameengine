//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_SUB_OUT_OF_RANGE_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_SUB_OUT_OF_RANGE_IMPL_HPP_INCLUDED

#include <sge/image/box.hpp>
#include <sge/image/view/sub_out_of_range.hpp>
#include <fcppt/format.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/box/output.hpp>

template <typename Tag>
sge::image::view::sub_out_of_range<Tag>::sub_out_of_range(box const &_outer, box const &_inner)
    : sge::image::exception(
          (fcppt::format(FCPPT_TEXT("sub_out_of_range: %1% not in %2%!")) % _inner % _outer).str()),
      outer_(_outer),
      inner_(_inner)
{
}

template <typename Tag>
sge::image::view::sub_out_of_range<Tag>::sub_out_of_range(sub_out_of_range &&) noexcept = default;

template <typename Tag>
sge::image::view::sub_out_of_range<Tag>::sub_out_of_range(sub_out_of_range const &) = default;

template <typename Tag>
sge::image::view::sub_out_of_range<Tag> &
sge::image::view::sub_out_of_range<Tag>::operator=(sub_out_of_range &&) noexcept = default;

template <typename Tag>
sge::image::view::sub_out_of_range<Tag> &
sge::image::view::sub_out_of_range<Tag>::operator=(sub_out_of_range const &) = default;

template <typename Tag>
typename sge::image::view::sub_out_of_range<Tag>::box const &
sge::image::view::sub_out_of_range<Tag>::outer() const
{
  return outer_;
}

template <typename Tag>
typename sge::image::view::sub_out_of_range<Tag>::box const &
sge::image::view::sub_out_of_range<Tag>::inner() const
{
  return inner_;
}

namespace sge::image::view
{
template <typename Tag>
sub_out_of_range<Tag>::~sub_out_of_range() noexcept = default;
}

#endif
