//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/box_fwd.hpp>
#include <sge/image/impl/view/instantiate_const_nonconst.hpp>
#include <sge/image/impl/view/sub_impl.hpp>

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB_BASE(tag, object_type) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::image::view::object_type<tag> \
  sge::image::view::sub<tag>( \
      sge::image::view::object_type<tag> const &, sge::image::box<tag> const &)

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB(tag) \
  SGE_IMAGE_IMPL_VIEW_INSTANTIATE_CONST_NONCONST(tag, SGE_IMAGE_IMPL_VIEW_INSTANTIATE_SUB_BASE)

#endif
