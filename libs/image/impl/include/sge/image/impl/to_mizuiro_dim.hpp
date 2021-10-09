//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_TO_MIZUIRO_DIM_HPP_INCLUDED
#define SGE_IMAGE_IMPL_TO_MIZUIRO_DIM_HPP_INCLUDED

#include <mizuiro/image/dimension.hpp>
#include <fcppt/use.hpp>
#include <fcppt/array/init.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/at.hpp>
#include <fcppt/math/dim/object_impl.hpp>

namespace sge::image::impl
{

template <typename T, fcppt::math::size_type N, typename S>
mizuiro::image::dimension<N, T> to_mizuiro_dim(fcppt::math::dim::object<T, N, S> const &_src)
{
  using result_type = mizuiro::image::dimension<N, T>;

  return result_type{fcppt::array::init<typename result_type::array_type>(
      [&_src](auto const _index)
      {
        FCPPT_USE(_index);

        return fcppt::math::dim::at<decltype(_index)::value>(_src);
      })};
}

}

#endif
