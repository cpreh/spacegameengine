//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_INSTANTIATE_MANAGER_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_INSTANTIATE_MANAGER_HPP_INCLUDED

#include <sge/core/impl/export_function_instantiation.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/impl/manager_impl.hpp>

#define SGE_PLUGIN_IMPL_INSTANTIATE_MANAGER(plugin_type) \
  template SGE_CORE_IMPL_EXPORT_FUNCTION_INSTANTIATION sge::plugin::collection<plugin_type> \
  sge::plugin::manager::collection<plugin_type>()

#endif
