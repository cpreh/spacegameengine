//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_PLUGIN_TRAITS_HPP_INCLUDED
#define SGE_INPUT_PLUGIN_TRAITS_HPP_INCLUDED

#include <sge/input/system_fwd.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/plugin/capabilities_fwd.hpp>
#include <sge/plugin/detail/address_name.hpp>
#include <sge/plugin/detail/traits.hpp>


namespace sge
{
namespace plugin
{
namespace detail
{

template<>
struct traits<
	sge::input::system
>
{
	SGE_INPUT_DETAIL_SYMBOL
	static
	sge::plugin::detail::address_name
	plugin_loader_name();

	SGE_INPUT_DETAIL_SYMBOL
	static
	sge::plugin::capabilities
	plugin_type();

	using
	loader_function
	=
	sge::input::system_unique_ptr();
};

}
}
}

#endif
