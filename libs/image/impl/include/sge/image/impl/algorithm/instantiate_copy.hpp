//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/algorithm/may_overlap.hpp> // IWYU pragma: keep
#include <sge/image/algorithm/uninitialized.hpp> // IWYU pragma: keep
#include <sge/image/impl/algorithm/copy_impl.hpp> // IWYU pragma: keep
#include <sge/image/view/const_object_fwd.hpp> // IWYU pragma: keep
#include <sge/image/view/object_fwd.hpp> // IWYU pragma: keep

#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY(tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION void sge::image::algorithm::copy<tag>( \
      sge::image::view::const_object<tag> const &, \
      sge::image::view::object<tag> const &, \
      sge::image::algorithm::may_overlap, \
      sge::image::algorithm::uninitialized)

#endif
