//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_MAIN_AREA_SCREEN_CORNER_HPP_INCLUDED
#define SGE_GUI_MAIN_AREA_SCREEN_CORNER_HPP_INCLUDED

#include <sge/gui/context_ref.hpp>
#include <sge/gui/gravity_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/viewport_adaptor.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/expander.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::main_area
{

class screen_corner : public sge::gui::main_area::base
{
  FCPPT_NONMOVABLE(screen_corner);

public:
  SGE_GUI_DETAIL_SYMBOL
  screen_corner(
      sge::renderer::device::core_ref,
      sge::viewport::manager_ref,
      sge::gui::context_ref,
      sge::gui::widget::reference,
      sge::gui::gravity);

  SGE_GUI_DETAIL_SYMBOL
  ~screen_corner() override;

  SGE_GUI_DETAIL_SYMBOL
  void relayout() override;

private:
  sge::gui::widget::base &widget() override;

  sge::gui::widget::reference const widget_;

  sge::gui::widget::minimum_size minimum_size_;

  sge::gui::widget::expander horizontal_expander_;

  sge::gui::widget::expander vertical_expander_;

  sge::gui::widget::box_container horizontal_container_;

  sge::gui::widget::box_container vertical_container_;

  sge::gui::main_area::viewport_adaptor viewport_adaptor_;
};

}

#endif
