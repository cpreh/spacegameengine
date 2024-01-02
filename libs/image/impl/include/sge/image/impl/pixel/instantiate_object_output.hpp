//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_PIXEL_INSTANTIATE_OBJECT_OUTPUT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_PIXEL_INSTANTIATE_OBJECT_OUTPUT_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/impl/pixel/object_output_impl.hpp> // IWYU pragma: keep
#include <sge/image/pixel/object.hpp> // IWYU pragma: keep
#include <fcppt/io/ostream_fwd.hpp> // IWYU pragma: keep

#define SGE_IMAGE_IMPL_PIXEL_INSTANTIATE_OBJECT_OUTPUT(tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION fcppt::io::ostream & \
  sge::image::pixel::operator<<<tag>(fcppt::io::ostream &, sge::image::pixel::object<tag> const &)

#endif
