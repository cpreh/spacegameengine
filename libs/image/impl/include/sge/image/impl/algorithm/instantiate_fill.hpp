//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_FILL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_FILL_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/fill_impl.hpp>
#include <sge/image/pixel/object_fwd.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/view/object_fwd.hpp>

#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_FILL(tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION void sge::image::algorithm::fill<tag>( \
      sge::image::view::object<tag> const &, \
      sge::image::pixel::object<sge::image::traits::image::color_tag<tag>> const &, \
      sge::image::algorithm::uninitialized)

#endif
