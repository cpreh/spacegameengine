//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST_HPP_INCLUDED

#include <fcppt/config/platform.hpp>

#ifdef FCPPT_CONFIG_POSIX_PLATFORM

#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST \
); \
  }

#elifdef FCPPT_CONFIG_WINDOWS_PLATFORM

#include <sge/plugin/library/function_map.hpp>
#include <fcppt/symbol/export.hpp>

#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST \
    ); \
  } \
  extern "C" \
  { \
    FCPPT_SYMBOL_EXPORT \
    sge::plugin::library::function_map const *sge_plugin_functions(); \
\
    sge::plugin::library::function_map const *sge_plugin_functions() \
    { \
      return &sge_plugin_functions_global; \
    } \
  }

#else
#error "Don't know what the library interface should look like!"
#endif

#endif
