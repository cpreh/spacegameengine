//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/impl/store/view_impl.hpp>
#include <sge/image/store/object_fwd.hpp>
#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image/view/object_fwd.hpp>
#include <fcppt/reference_impl.hpp>

#define SGE_IMAGE_IMPL_STORE_INSTANTIATE_VIEW(tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::image::view::object<tag> \
  sge::image::store::view<tag>(fcppt::reference<sge::image::store::object<tag>>); \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::image::view::const_object<tag> \
  sge::image::store::view<tag>(fcppt::reference<sge::image::store::object<tag> const>)

#endif
