//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/exception.hpp>
#include <sge/cegui/toolbox/append_row.hpp>
#include <sge/cegui/toolbox/row.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_int_range.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/widgets/ListboxTextItem.h>
#include <CEGUI/widgets/MultiColumnList.h>
#include <fcppt/config/external_end.hpp>

void sge::cegui::toolbox::append_row(
    CEGUI::MultiColumnList &_list, sge::cegui::toolbox::row const &_mapper)
{
  if (static_cast<sge::cegui::toolbox::row::size_type>(_list.getColumnCount()) != _mapper.size())
  {
    throw sge::cegui::exception{FCPPT_TEXT("toolbox::append_row: Invalid size!")};
  }

  if (_mapper.empty())
  {
    throw sge::cegui::exception{FCPPT_TEXT("toolbox::append_row: mapper is empty!")};
  }

  CEGUI::uint const index(_list.addRow(
      // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
      new CEGUI::ListboxTextItem(_mapper[0], 0, nullptr),
      0));

  for (sge::cegui::toolbox::row::size_type const cur : fcppt::make_int_range(
           fcppt::literal<sge::cegui::toolbox::row::size_type>(1U), _mapper.size()))
  {
    _list.setItem(
        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        new CEGUI::ListboxTextItem(_mapper[cur], 0, nullptr),
        static_cast<CEGUI::uint>(cur),
        index);
  }
}
