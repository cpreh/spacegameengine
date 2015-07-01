#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_name_pair.hpp>
#include <sge/font/string.hpp>


sge::gui::widget::reference_name_pair::reference_name_pair(
	sge::gui::widget::reference const _reference,
	sge::font::string const &_name
)
:
	reference_(
		_reference
	),
	name_(
		_name
	)
{
}

sge::gui::widget::reference const
sge::gui::widget::reference_name_pair::reference() const
{
	return
		reference_;
}

sge::font::string const &
sge::gui::widget::reference_name_pair::name() const
{
	return
		name_;
}
