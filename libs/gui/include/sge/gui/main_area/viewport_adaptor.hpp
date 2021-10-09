//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_MAIN_AREA_VIEWPORT_ADAPTOR_HPP_INCLUDED
#define SGE_GUI_MAIN_AREA_VIEWPORT_ADAPTOR_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/rucksack/viewport/adaptor.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::main_area
{

class viewport_adaptor : public sge::gui::main_area::base
{
  FCPPT_NONMOVABLE(viewport_adaptor);

public:
  SGE_GUI_DETAIL_SYMBOL
  viewport_adaptor(
      sge::renderer::device::core_ref, sge::viewport::manager_ref, sge::gui::widget::reference);

  SGE_GUI_DETAIL_SYMBOL
  ~viewport_adaptor() override;

  SGE_GUI_DETAIL_SYMBOL
  void relayout() override;

private:
  sge::gui::widget::base &widget() override;

  sge::gui::widget::reference const widget_;

  sge::rucksack::viewport::adaptor impl_;
};

}

#endif
