//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_MAIN_AREA_FIXED_POSITION_HPP_INCLUDED
#define SGE_GUI_MAIN_AREA_FIXED_POSITION_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::main_area
{

class fixed_position : public sge::gui::main_area::base
{
  FCPPT_NONMOVABLE(fixed_position);

public:
  SGE_GUI_DETAIL_SYMBOL
  fixed_position(sge::gui::widget::reference, sge::rucksack::vector const &);

  SGE_GUI_DETAIL_SYMBOL
  ~fixed_position() override;

  SGE_GUI_DETAIL_SYMBOL
  void relayout() override;

private:
  sge::gui::widget::base &widget() override;

  void do_relayout();

  sge::gui::widget::reference const widget_;

  sge::gui::widget::minimum_size minimum_size_;
};

}

#endif
