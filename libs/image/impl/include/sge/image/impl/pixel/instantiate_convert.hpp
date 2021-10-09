//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_PIXEL_INSTANTIATE_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_PIXEL_INSTANTIATE_CONVERT_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/impl/pixel/convert_impl.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/pixel/object_fwd.hpp>

#define SGE_IMAGE_IMPL_PIXEL_INSTANTIATE_CONVERT(tag, format) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION \
      sge::image::enable_if_has_format<tag, format, sge::image::pixel::mizuiro_type<format>> \
      sge::image::pixel::convert<tag, format>(sge::image::pixel::object<tag> const &)

#endif
