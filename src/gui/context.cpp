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

sge::gui::widget::optional_ref const
sge::gui::context::focus() const
{
	return
		focus_;
}
