//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_LIBRARY_LOAD_FUNCTION_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_LOAD_FUNCTION_HPP_INCLUDED

#include <sge/plugin/impl/library/from_function_base_unsafe.hpp>
#include <sge/plugin/impl/library/load_function_base.hpp>
#include <sge/plugin/library/object_fwd.hpp>
#include <sge/plugin/library/symbol_string.hpp>


namespace sge
{
namespace plugin
{
namespace impl
{
namespace library
{

template<
	typename Function
>
Function
load_function(
	sge::plugin::library::object &_object,
	sge::plugin::library::symbol_string const &_symbol
)
{
	return
		sge::plugin::impl::library::from_function_base_unsafe<
			Function
		>(
			sge::plugin::impl::library::load_function_base(
				_object,
				_symbol
			)
		);
}

}
}
}
}

#endif
