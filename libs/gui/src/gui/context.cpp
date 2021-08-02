//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/context.hpp>
#include <sge/gui/focus_change.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/gui/widget/reference.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_const.hpp>
#include <fcppt/optional/maybe_void.hpp>


sge::gui::context::context()
:
	focus_()
{
}

sge::gui::context::~context()
= default;

void
sge::gui::context::focus(
	sge::gui::widget::reference const _widget
)
{
	fcppt::optional::maybe_void(
		focus_,
		[](
			fcppt::reference<
				sge::gui::widget::base
			> const _focus
		)
		{
			_focus.get().on_focus_changed(
				sge::gui::focus_change::lost
			);
		}
	);

	focus_ =
		sge::gui::widget::optional_ref(
			_widget
		);

	_widget.get().on_focus_changed(
		sge::gui::focus_change::gained
	);
}

void
sge::gui::context::destroy(
	sge::gui::widget::base const &_widget
)
{
	fcppt::optional::maybe_void(
		focus_,
		[
			&_widget,
			this
		](
			fcppt::reference<
				sge::gui::widget::base
			> const _focus
		)
		{
			if(
				fcppt::reference_to_const(
					_focus
				)
				==
				fcppt::make_cref(
					_widget
				)
			)
			{
				focus_ =
					sge::gui::widget::optional_ref();
			}
		}
	);
}

sge::gui::widget::optional_ref
sge::gui::context::focus() const
{
	return
		focus_;
}
