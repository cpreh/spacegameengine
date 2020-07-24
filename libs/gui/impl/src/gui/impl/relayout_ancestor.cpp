//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/impl/relayout_ancestor.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <fcppt/make_ref.hpp>


void
sge::gui::impl::relayout_ancestor(
	sge::gui::widget::base &_widget
)
{
	sge::rucksack::widget::optional_ref layout(
		fcppt::make_ref(
			_widget.layout()
		)
	);

	// TODO(philipp): Do this differently!
	while(
		layout.get_unsafe().get().parent().has_value()
	)
	{
		layout =
			layout.get_unsafe().get().parent();
	}

	layout.get_unsafe().get().relayout();
}
