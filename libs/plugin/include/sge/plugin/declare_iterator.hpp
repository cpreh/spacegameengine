//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_DECLARE_ITERATOR_HPP_INCLUDED
#define SGE_PLUGIN_DECLARE_ITERATOR_HPP_INCLUDED

#include <sge/core/detail/export_class_declaration.hpp>
#include <sge/plugin/iterator.hpp>

#define SGE_PLUGIN_DECLARE_ITERATOR(plugin_type) \
  extern template class SGE_CORE_DETAIL_EXPORT_CLASS_DECLARATION sge::plugin::iterator<plugin_type>

#endif
