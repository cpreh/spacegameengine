//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_CURSOR_OPTION_HPP_INCLUDED
#define SGE_SYSTEMS_CURSOR_OPTION_HPP_INCLUDED

#include <sge/systems/cursor_option_fwd.hpp> // IWYU pragma: keep
#include <fcppt/enum/define_max_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::systems
{

enum class cursor_option : std::uint8_t
{
  exclusive
};

}

FCPPT_ENUM_DEFINE_MAX_VALUE(sge::systems::cursor_option::exclusive);

#endif
