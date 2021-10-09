//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/to_wstring.hpp>
#include <sge/cegui/impl/prefix.hpp>
#include <sge/cegui/impl/to_absolute_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

std::filesystem::path sge::cegui::impl::to_absolute_path(
    sge::cegui::impl::prefix const &_prefix, CEGUI::String const &_filename)
{
  return _prefix.get() / sge::cegui::to_wstring(_filename);
}
