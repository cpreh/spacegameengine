//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_INSTANTIATE_FROM_LOADER_FUNCTION_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_INSTANTIATE_FROM_LOADER_FUNCTION_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/plugin/loader_function.hpp>
#include <sge/plugin/impl/detail/from_loader_function.hpp>
#include <sge/plugin/library/function_base.hpp>

#define SGE_PLUGIN_IMPL_INSTANTIATE_FROM_LOADER_FUNCTION(plugin_type) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::plugin::library::function_base \
  sge::plugin::detail::from_loader_function<plugin_type>( \
      sge::plugin::loader_function<plugin_type>)

#endif
