//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_IMPL_LIBRARY_LOADED_SYMBOL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_LOADED_SYMBOL_HPP_INCLUDED

#include <fcppt/config/platform.hpp>
#ifdef FCPPT_CONFIG_WINDOWS_PLATFORM
#include <sge/core/impl/include_windows.hpp>
#endif

namespace sge::plugin::impl::library
{

#ifdef FCPPT_CONFIG_POSIX_PLATFORM
using loaded_symbol = void *;
#elifdef FCPPT_CONFIG_WINDOWS_PLATFORM
using loaded_symbol = FARPROC;
#else
#error "Don't know what a library's symbol is!"
#endif

}

#endif
