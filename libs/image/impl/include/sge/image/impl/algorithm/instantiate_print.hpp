//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_PRINT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_PRINT_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/impl/algorithm/print_impl.hpp> // IWYU pragma: keep
#include <sge/image/view/const_object.hpp> // IWYU pragma: keep
#include <fcppt/io/ostream_fwd.hpp> // IWYU pragma: keep

#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_PRINT(tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION void sge::image::algorithm::print<tag>( \
      fcppt::io::ostream &, sge::image::view::const_object<tag> const &)

#endif
