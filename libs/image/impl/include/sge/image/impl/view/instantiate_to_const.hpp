//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_INSTANTIATE_TO_CONST_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_TO_CONST_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/image/impl/view/to_const_impl.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>

#define SGE_IMAGE_IMPL_VIEW_INSTANTIATE_TO_CONST(Tag) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::image::view::const_object<Tag> \
  sge::image::view::to_const<Tag>(sge::image::view::object<Tag> const &)

#endif
