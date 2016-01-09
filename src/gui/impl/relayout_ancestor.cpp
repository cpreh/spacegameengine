/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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

	// TODO: Do this differently!
	while(
		layout.get_unsafe().get().parent().has_value()
	)
		layout =
			layout.get_unsafe().get().parent();

	layout.get_unsafe().get().relayout();
}
