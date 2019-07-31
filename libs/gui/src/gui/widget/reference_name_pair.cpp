//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/string.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_name_pair.hpp>


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

sge::gui::widget::reference
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
