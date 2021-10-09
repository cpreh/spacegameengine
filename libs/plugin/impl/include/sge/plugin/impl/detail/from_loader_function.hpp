//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_DETAIL_FROM_LOADER_FUNCTION_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_DETAIL_FROM_LOADER_FUNCTION_HPP_INCLUDED

#include <sge/plugin/loader_function.hpp>
#include <sge/plugin/detail/from_loader_function.hpp>
#include <sge/plugin/impl/library/to_function_base_unsafe.hpp>
#include <sge/plugin/library/function_base.hpp>

template <typename Type>
sge::plugin::library::function_base
sge::plugin::detail::from_loader_function(sge::plugin::loader_function<Type> const _function)
{
  return sge::plugin::impl::library::to_function_base_unsafe(_function);
}

#endif
