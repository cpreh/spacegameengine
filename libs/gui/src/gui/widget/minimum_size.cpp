//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>
#include <fcppt/make_ref.hpp>


sge::gui::widget::minimum_size::minimum_size(
	sge::gui::widget::reference const _widget
)
:
	sge::gui::widget::dummy(),
	layout_(
		fcppt::make_ref(
			_widget.get().layout()
		)
	)
{
}

sge::gui::widget::minimum_size::~minimum_size()
= default;

sge::rucksack::widget::base &
sge::gui::widget::minimum_size::layout()
{
	return
		layout_;
}
