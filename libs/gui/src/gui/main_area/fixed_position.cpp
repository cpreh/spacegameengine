//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/fixed_position.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>


sge::gui::main_area::fixed_position::fixed_position(
	sge::gui::widget::reference const _widget,
	sge::rucksack::vector const &_position
)
:
	sge::gui::main_area::base(),
	widget_(
		_widget
	),
	minimum_size_(
		widget_
	)
{
	minimum_size_.layout().position(
		_position
	);

	this->do_relayout();
}

sge::gui::main_area::fixed_position::~fixed_position()
= default;

void
sge::gui::main_area::fixed_position::relayout()
{
	this->do_relayout();
}

sge::gui::widget::base &
sge::gui::main_area::fixed_position::widget()
{
	return
		widget_.get();
}

void
sge::gui::main_area::fixed_position::do_relayout()
{
	minimum_size_.layout().relayout();
}
