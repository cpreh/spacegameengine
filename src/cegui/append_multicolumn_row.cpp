#include <sge/cegui/append_multicolumn_row.hpp>
#include <CEGUI/CEGUIBase.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
#include <fcppt/assert.hpp>

void
sge::cegui::append_multicolumn_row(
	CEGUI::MultiColumnList &list,
	column_sequence const &mapper)
{
	FCPPT_ASSERT(
		static_cast<column_sequence::size_type>(list.getColumnCount()) == mapper.size());
	CEGUI::uint const index = 
		list.addRow(
			new CEGUI::ListboxTextItem(
				mapper[0]),
			0);
	for(column_sequence::size_type i = 1; i < mapper.size(); ++i)
		list.setItem(
			new CEGUI::ListboxTextItem(
				mapper[i]),
			static_cast<CEGUI::uint>(
				i),
			index);
}
