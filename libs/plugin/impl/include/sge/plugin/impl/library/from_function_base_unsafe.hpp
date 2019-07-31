//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_IMPL_LIBRARY_FROM_FUNCTION_BASE_UNSAFE_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_LIBRARY_FROM_FUNCTION_BASE_UNSAFE_HPP_INCLUDED

#include <sge/plugin/impl/library/cast_function_unsafe.hpp>
#include <sge/plugin/library/function_base.hpp>


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
inline
Function
from_function_base_unsafe(
	sge::plugin::library::function_base const _function
)
{
	return
		sge::plugin::impl::library::cast_function_unsafe<
			Function
		>(
			_function
		);
}

}
}
}
}

#endif
