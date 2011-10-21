/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cegui/toolbox/append_row.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <elements/CEGUIListboxTextItem.h>
#include <CEGUIBase.h>
#include <fcppt/config/external_end.hpp>


void
sge::cegui::toolbox::append_row(
	CEGUI::MultiColumnList &list,
	row const &mapper)
{
	FCPPT_ASSERT_PRE(
		static_cast<row::size_type>(list.getColumnCount()) == mapper.size());
	CEGUI::uint const index =
		list.addRow(
			new CEGUI::ListboxTextItem(
				mapper[0]),
			0);
	for(row::size_type i = 1; i < mapper.size(); ++i)
		list.setItem(
			new CEGUI::ListboxTextItem(
				mapper[i]),
			static_cast<CEGUI::uint>(
				i),
			index);
}
