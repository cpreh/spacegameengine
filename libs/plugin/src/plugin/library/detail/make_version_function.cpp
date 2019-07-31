//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/impl/library/to_function_base_unsafe.hpp>
#include <sge/plugin/impl/library/version_function_name.hpp>
#include <sge/plugin/library/function_base_pair.hpp>
#include <sge/plugin/library/detail/make_version_function.hpp>
#include <sge/plugin/library/detail/version_function.hpp>


sge::plugin::library::function_base_pair
sge::plugin::library::detail::make_version_function(
	sge::plugin::library::detail::version_function const _function
)
{
	return
		sge::plugin::library::function_base_pair{
			sge::plugin::impl::library::version_function_name(),
			sge::plugin::impl::library::to_function_base_unsafe(
				_function
			)
		};
}
