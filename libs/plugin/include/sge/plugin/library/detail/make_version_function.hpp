//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_LIBRARY_DETAIL_MAKE_VERSION_FUNCTION_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_DETAIL_MAKE_VERSION_FUNCTION_HPP_INCLUDED

#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/function_base_pair.hpp>
#include <sge/plugin/library/detail/version_function.hpp>


namespace sge
{
namespace plugin
{
namespace library
{
namespace detail
{

SGE_PLUGIN_DETAIL_SYMBOL
sge::plugin::library::function_base_pair
make_version_function(
	sge::plugin::library::detail::version_function
);

}
}
}
}

#endif
