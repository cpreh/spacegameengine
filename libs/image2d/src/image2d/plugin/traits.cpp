//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/plugin/traits.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/detail/address_name.hpp>
#include <sge/plugin/impl/address_name.hpp>


sge::plugin::detail::address_name
sge::plugin::detail::traits<
	sge::image2d::system
>::plugin_loader_name()
{
	return
		SGE_PLUGIN_IMPL_ADDRESS_NAME(
			"create_image2d_system"
		);
}

sge::plugin::capabilities
sge::plugin::detail::traits<
	sge::image2d::system
>::plugin_type()
{
	return
		sge::plugin::capabilities::image2d_system;
}
