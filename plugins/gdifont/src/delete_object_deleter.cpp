//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>

void sge::gdifont::delete_object_deleter::operator()(HGDIOBJ const _object) const noexcept
{
  if (_object != nullptr)
  {
    if(::DeleteObject(_object) == 0)
    {
      std::terminate();
    }
  }
}
