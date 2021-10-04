//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_MERGE_CONFIG_STRINGS_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_MERGE_CONFIG_STRINGS_HPP_INCLUDED

#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/systems/optional_name_fwd.hpp>


namespace sge::systems::impl
{

sge::systems::optional_name
merge_config_strings(
	sge::systems::optional_name const &,
	sge::parse::ini::optional_start const &,
	sge::parse::ini::entry_name const &
);

}

#endif
