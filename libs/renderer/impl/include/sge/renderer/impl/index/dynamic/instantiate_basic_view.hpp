//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_IMPL_INDEX_DYNAMIC_INSTANTIATE_BASIC_VIEW_HPP_INCLUDED
#define SGE_RENDERER_IMPL_INDEX_DYNAMIC_INSTANTIATE_BASIC_VIEW_HPP_INCLUDED

#include <sge/core/impl/export_class_instantiation.hpp>
#include <sge/renderer/impl/index/dynamic/basic_view_impl.hpp> // IWYU pragma: keep

#define SGE_RENDERER_IMPL_INDEX_DYNAMIC_INSTANTIATE_BASIC_VIEW(name) \
  template class SGE_CORE_IMPL_EXPORT_CLASS_INSTANTIATION \
      sge::renderer::index::dynamic::basic_view<name>

#endif
