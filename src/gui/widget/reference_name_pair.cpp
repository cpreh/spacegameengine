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
