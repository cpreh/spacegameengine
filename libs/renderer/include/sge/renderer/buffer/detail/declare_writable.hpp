//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_BUFFER_DETAIL_DECLARE_WRITABLE_HPP_INCLUDED
#define SGE_RENDERER_BUFFER_DETAIL_DECLARE_WRITABLE_HPP_INCLUDED

#include <sge/core/detail/export_class_declaration.hpp>
#include <sge/renderer/buffer/writable.hpp> // IWYU pragma: keep

#define SGE_RENDERER_BUFFER_DETAIL_DECLARE_WRITABLE(tag) \
  extern template class SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION \
      sge::renderer::buffer::writable<tag>

#endif
