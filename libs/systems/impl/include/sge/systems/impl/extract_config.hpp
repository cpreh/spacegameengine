//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_EXTRACT_CONFIG_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_EXTRACT_CONFIG_HPP_INCLUDED

#include <sge/systems/config_fwd.hpp>
#include <sge/systems/detail/any_map.hpp>

namespace sge::systems::impl
{

sge::systems::config extract_config(sge::systems::detail::any_map const &);

}

#endif
