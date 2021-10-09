//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_CLONE_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_CLONE_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/impl/algorithm/clone_impl.hpp>
#include <sge/image/store/object.hpp>
#include <sge/image/view/const_object.hpp>

#define SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_CLONE(tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::image::store::object<tag> \
  sge::image::algorithm::clone<tag>(sge::image::view::const_object<tag> const &)

#endif
