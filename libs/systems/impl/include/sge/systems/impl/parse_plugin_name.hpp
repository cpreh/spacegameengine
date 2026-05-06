//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_PARSE_PLUGIN_NAME_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_PARSE_PLUGIN_NAME_HPP_INCLUDED

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/systems/optional_name.hpp>
#include <fcppt/log/object_fwd.hpp>

namespace sge::systems::impl
{

[[nodiscard]]
sge::systems::optional_name parse_plugin_name(
    fcppt::log::object &,
    sge::parse::ini::optional_start const &,
    sge::parse::ini::entry_name const &);

}

#endif
