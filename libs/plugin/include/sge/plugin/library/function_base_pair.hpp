//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_LIBRARY_FUNCTION_BASE_PAIR_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_FUNCTION_BASE_PAIR_HPP_INCLUDED

#include <sge/plugin/library/function_base.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::plugin::library
{

using function_base_pair =
    std::pair<sge::plugin::library::symbol_string, sge::plugin::library::function_base>;

}

#endif
