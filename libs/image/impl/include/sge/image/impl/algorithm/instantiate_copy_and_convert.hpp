//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY_AND_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY_AND_CONVERT_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/copy_and_convert_impl.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>

#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_COPY_AND_CONVERT(tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION void \
  sge::image::algorithm::copy_and_convert<tag>( \
      sge::image::view::const_object<tag> const &, \
      sge::image::view::object<tag> const &, \
      sge::image::algorithm::may_overlap, \
      sge::image::algorithm::uninitialized)

#endif
