//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RUCKSACK_WIDGET_ENUMERATION_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_ENUMERATION_HPP_INCLUDED

#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::rucksack::widget
{

/**
 * The enumeration widget starts aligning its child widgets from left to right
 * until there's no more space on the right. Then, it creates a new row and
 * again, aligns from the left to right (like a word processor does with words).
 */
class enumeration : public sge::rucksack::widget::base
{
  FCPPT_NONMOVABLE(enumeration);

public:
  SGE_RUCKSACK_DETAIL_SYMBOL
  explicit enumeration(sge::rucksack::padding const &);

  SGE_RUCKSACK_DETAIL_SYMBOL
  void size(sge::rucksack::dim const &) override;

  SGE_RUCKSACK_DETAIL_SYMBOL
  void position(sge::rucksack::vector const &) override;

  [[nodiscard]] SGE_RUCKSACK_DETAIL_SYMBOL sge::rucksack::dim size() const override;

  [[nodiscard]] SGE_RUCKSACK_DETAIL_SYMBOL sge::rucksack::vector position() const override;

  [[nodiscard]] SGE_RUCKSACK_DETAIL_SYMBOL sge::rucksack::axis_policy2 axis_policy() const override;

  SGE_RUCKSACK_DETAIL_SYMBOL
  void relayout() override;

  SGE_RUCKSACK_DETAIL_SYMBOL
  void push_back_child(sge::rucksack::widget::reference);

  SGE_RUCKSACK_DETAIL_SYMBOL
  ~enumeration() override;

private:
  using child_information = std::vector<sge::rucksack::widget::reference>;

  sge::rucksack::padding const padding_;

  child_information children_;

  sge::rucksack::vector position_;

  sge::rucksack::dim size_;

  void child_destroyed(sge::rucksack::widget::base & // NOLINT(google-runtime-references)
                       ) override;
};

}

#endif
