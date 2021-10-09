//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_GUI_WIDGET_PREFERRED_SIZE_HPP_INCLUDED
#define SGE_GUI_WIDGET_PREFERRED_SIZE_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::gui::widget
{

class preferred_size : public sge::gui::widget::dummy
{
  FCPPT_NONMOVABLE(preferred_size);

public:
  SGE_GUI_DETAIL_SYMBOL
  explicit preferred_size(sge::rucksack::dim const &);

  SGE_GUI_DETAIL_SYMBOL
  ~preferred_size() override;

  [[nodiscard]] sge::rucksack::widget::base &layout() override;

private:
  sge::rucksack::widget::dummy layout_;
};

}

#endif
