//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/parse/ini/section_name.hpp>
#include <sge/systems/impl/ini_section_name.hpp>

sge::parse::ini::section_name sge::systems::impl::ini_section_name()
{
  return sge::parse::ini::section_name("systems");
}
