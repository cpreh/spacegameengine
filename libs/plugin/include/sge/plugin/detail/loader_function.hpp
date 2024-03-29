//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PLUGIN_DETAIL_LOADER_FUNCTION_HPP_INCLUDED
#define SGE_PLUGIN_DETAIL_LOADER_FUNCTION_HPP_INCLUDED

#include <sge/plugin/detail/loader_function_tpl.hpp>

namespace sge::plugin::detail
{

template <typename Type>
using loader_function = typename sge::plugin::detail::loader_function_tpl<Type>::type;

}

#endif
