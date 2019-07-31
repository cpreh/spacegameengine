//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_DECLARE_MANAGER_HPP_INCLUDED
#define SGE_PLUGIN_DECLARE_MANAGER_HPP_INCLUDED

#include <sge/plugin/collection.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>


#define SGE_PLUGIN_DECLARE_MANAGER(\
	plugin_type\
)\
extern \
template \
SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL \
sge::plugin::collection<\
	plugin_type\
> \
sge::plugin::manager::collection<\
	plugin_type\
>()

#endif
