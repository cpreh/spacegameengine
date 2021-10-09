//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_LIBRARY_DETAIL_VERSION_FUNCTION_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_DETAIL_VERSION_FUNCTION_HPP_INCLUDED

#include <sge/plugin/info_fwd.hpp>

namespace sge::plugin::library::detail
{

using version_function = sge::plugin::info (*)();

}

#endif
