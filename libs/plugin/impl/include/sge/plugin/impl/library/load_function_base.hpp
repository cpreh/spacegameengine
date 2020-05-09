//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_LIBRARY_LOAD_FUNCTION_BASE_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_LOAD_FUNCTION_BASE_HPP_INCLUDED

#include <sge/plugin/detail/symbol.hpp>
#include <sge/plugin/library/function_base.hpp>
#include <sge/plugin/library/object_fwd.hpp>
#include <sge/plugin/library/symbol_string.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sge
{
namespace plugin
{
namespace impl
{
namespace library
{

SGE_PLUGIN_DETAIL_SYMBOL
sge::plugin::library::function_base
load_function_base(
	fcppt::reference<
		sge::plugin::library::object
	>,
	sge::plugin::library::symbol_string const &
);

}
}
}
}

#endif
