//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_DETAIL_FROM_LOADER_FUNCTION_HPP_INCLUDED
#define SGE_PLUGIN_DETAIL_FROM_LOADER_FUNCTION_HPP_INCLUDED

#include <sge/plugin/loader_function.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>
#include <sge/plugin/library/function_base.hpp>


namespace sge::plugin::detail
{

template<
	typename Type
>
SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
sge::plugin::library::function_base
from_loader_function(
	sge::plugin::loader_function<
		Type
	>
);

}

#endif
