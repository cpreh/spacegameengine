//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_WINDOW_MAKE_SYSTEM_BASE_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_MAKE_SYSTEM_BASE_HPP_INCLUDED

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/impl/window/system_base_unique_ptr.hpp>
#include <fcppt/log/context_fwd.hpp>


namespace sge
{
namespace systems
{
namespace impl
{
namespace window
{

sge::systems::impl::window::system_base_unique_ptr
make_system_base(
	fcppt::log::context &,
	sge::systems::window const &
);

}
}
}
}

#endif
