//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_ORIGINAL_WINDOW_HPP_INCLUDED
#define SGE_SYSTEMS_ORIGINAL_WINDOW_HPP_INCLUDED

#include <sge/systems/original_window_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/window/dim_fwd.hpp>
#include <sge/window/optional_dim.hpp>
#include <sge/window/title.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>

namespace sge::systems
{

class original_window
{
public:
  SGE_SYSTEMS_DETAIL_SYMBOL
  explicit original_window(sge::window::title &&);

  [[nodiscard]] SGE_SYSTEMS_DETAIL_SYMBOL sge::systems::original_window
  dim(sge::window::dim const &) &&;

  [[nodiscard]] SGE_SYSTEMS_DETAIL_SYMBOL sge::systems::original_window
  class_name(fcppt::string &&) &&;

  [[nodiscard]] SGE_SYSTEMS_DETAIL_SYMBOL sge::systems::original_window hide_cursor() &&;

  [[nodiscard]] sge::window::title const &title() const;

  [[nodiscard]] sge::window::optional_dim const &dim() const;

  [[nodiscard]] fcppt::optional_string const &class_name() const;

  [[nodiscard]] bool get_hide_cursor() const;

private:
  sge::window::title title_;

  fcppt::optional_string class_name_;

  sge::window::optional_dim dim_;

  bool hide_cursor_;
};

}

#endif
