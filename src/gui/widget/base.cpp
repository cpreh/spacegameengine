#include <sge/gui/duration.hpp>
#include <sge/gui/focus_change.hpp>
#include <sge/gui/get_focus.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/optional_focus.hpp>
#include <sge/gui/widget/optional_ref.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <fcppt/maybe_void.hpp>


sge::gui::widget::base::base()
:
	parent_(),
	enabled_(
		true
	)
{
}

sge::gui::widget::base::~base()
{
	fcppt::maybe_void(
		parent_,
		[
			this
		](
			sge::gui::widget::base &_parent
		)
		{
			_parent.unregister(
				*this
			);
		}
	);
}

void
sge::gui::widget::base::on_update(
	sge::gui::duration
)
{
}

sge::gui::get_focus const
sge::gui::widget::base::on_click(
	sge::rucksack::vector
)
{
	return
		sge::gui::get_focus(
			false
		);
}

void
sge::gui::widget::base::on_key(
	sge::input::keyboard::key_code
)
{
}

void
sge::gui::widget::base::on_char(
	sge::font::char_type
)
{
}

void
sge::gui::widget::base::on_focus_changed(
	sge::gui::focus_change
)
{
}

sge::gui::widget::optional_ref const
sge::gui::widget::base::on_tab(
	sge::gui::widget::optional_focus &
)
{
	return
		sge::gui::widget::optional_ref();
}

void
sge::gui::widget::base::parent(
	sge::gui::widget::optional_ref const _new_parent
)
{
	if(
		parent_.has_value()
	)
		this->layout().parent(
			sge::rucksack::widget::optional_ref()
		);

	parent_ =
		_new_parent;

	fcppt::maybe_void(
		_new_parent,
		[
			this
		](
			sge::gui::widget::base &_parent
		)
		{
			this->layout().parent(
				sge::rucksack::widget::optional_ref(
					_parent.layout()
				)
			);
		}
	);
}

void
sge::gui::widget::base::enable(
	bool const _enabled
)
{
	enabled_ =
		_enabled;
}

bool
sge::gui::widget::base::enabled() const
{
	return
		enabled_;
}

void
sge::gui::widget::base::unregister(
	sge::gui::widget::base const &
)
{
}
