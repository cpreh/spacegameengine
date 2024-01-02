//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_INSTANTIATE_INVALID_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_INSTANTIATE_INVALID_CONVERT_HPP_INCLUDED

#include <sge/core/impl/export_class_instantiation.hpp>
#include <sge/image/impl/invalid_convert_impl.hpp> // IWYU pragma: keep

#define SGE_IMAGE_IMPL_INSTANTIATE_INVALID_CONVERT(tag) \
  template class SGE_CORE_IMPL_EXPORT_CLASS_INSTANTIATION sge::image::invalid_convert<tag>

#endif
