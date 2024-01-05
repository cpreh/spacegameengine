//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_WITH_FONT_HPP_INCLUDED
#define SGE_SYSTEMS_WITH_FONT_HPP_INCLUDED

#include <sge/systems/font_fwd.hpp>
#include <sge/systems/with_font_fwd.hpp> // IWYU pragma: keep
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::systems
{

struct with_font
{
  using needs_init = std::false_type;

  using parameter_type = sge::systems::font;

  using needs_before = fcppt::mpl::list::object<>;
};

}

#endif
