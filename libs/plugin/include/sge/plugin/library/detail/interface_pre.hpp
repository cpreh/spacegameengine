//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE_HPP_INCLUDED

#include <sge/plugin/library/function_map.hpp>
#include <fcppt/config/platform.hpp>

#if defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <fcppt/symbol/export.hpp>

#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE \
  extern "C" \
  { \
    FCPPT_SYMBOL_EXPORT \
sge::plugin::library::function_map sge_plugin_functions(

#elif defined(FCPPT_CONFIG_WINDOWS_PLATFORM)

#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_PRE \
  namespace \
  { \
sge::plugin::library::function_map sge_plugin_functions_global(

#else
#error "Don't know what the library interface should look like!"
#endif

#endif
