#include <sge/cegui/toolbox/append_row.hpp>
#include <CEGUI/CEGUIBase.h>
#include <CEGUI/elements/CEGUIListboxTextItem.h>
#include <fcppt/assert.hpp>

void
sge::cegui::toolbox::append_row(
	CEGUI::MultiColumnList &list,
	row const &mapper)
{
	FCPPT_ASSERT(
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
