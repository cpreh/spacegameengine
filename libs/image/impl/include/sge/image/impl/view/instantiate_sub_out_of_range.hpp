//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB_OUT_OF_RANGE_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB_OUT_OF_RANGE_HPP_INCLUDED

#include <sge/core/impl/export_class_instantiation.hpp>
#include <sge/image/box.hpp> // IWYU pragma: keep
#include <sge/image/impl/view/sub_out_of_range_impl.hpp> // IWYU pragma: keep

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB_OUT_OF_RANGE(tag) \
  template class SGE_CORE_IMPL_EXPORT_CLASS_INSTANTIATION sge::image::view::sub_out_of_range<tag>

#endif
