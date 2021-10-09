//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_BACKGROUND_NONE_HPP_INCLUDED
#define SGE_GUI_BACKGROUND_NONE_HPP_INCLUDED

#include <sge/gui/background/base.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/reference.hpp>
#include <sge/gui/renderer/base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::background
{

class none : public sge::gui::background::base
{
  FCPPT_NONMOVABLE(none);

public:
  SGE_GUI_DETAIL_SYMBOL
  explicit none(sge::gui::main_area::reference);

  SGE_GUI_DETAIL_SYMBOL
  ~none() override;

private:
  void on_draw(
      sge::gui::renderer::base &, // NOLINT(google-runtime-references)
      sge::renderer::context::ffp &, // NOLINT(google-runtime-references)
      sge::rucksack::rect const &) override;
};

}

#endif
