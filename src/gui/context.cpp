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


#include <sge/gui/context.hpp>
#include <sge/gui/focus_change.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/assert/error.hpp>


sge::gui::context::context()
:
	focus_()
{
}

sge::gui::context::~context()
{
	FCPPT_ASSERT_ERROR(
		!focus_.has_value()
	);
}

void
sge::gui::context::focus(
	sge::gui::widget::base &_widget
)
{
	fcppt::maybe_void(
		focus_,
		[](
			sge::gui::widget::base &_focus
		)
		{
			_focus.on_focus_changed(
				sge::gui::focus_change::lost
			);
		}
	);

	focus_ =
		sge::gui::widget::optional_ref(
			_widget
		);

	_widget.on_focus_changed(
		sge::gui::focus_change::gained
	);
}

void
sge::gui::context::destroy(
	sge::gui::widget::base const &_widget
)
{
	fcppt::maybe_void(
		focus_,
		[
			&_widget,
			this
		](
			sge::gui::widget::base const &_focus
		)
		{
			if(
				&_focus
				==
				&_widget
			)
				focus_ =
					sge::gui::widget::optional_ref();
		}
	);
}

sge::gui::widget::optional_ref
sge::gui::context::focus() const
{
	return
		focus_;
}
