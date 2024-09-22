//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/find_path.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/evdev/joypad/optional_iterator.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

sge::evdev::joypad::optional_iterator
sge::evdev::joypad::find_path(sge::evdev::joypad::map &_map, std::filesystem::path const &_path)
{
  return fcppt::algorithm::find_if_opt(
      _map,
      [&_path](sge::evdev::joypad::map::value_type const &_value)
      { return _value.second->path() == _path; });
}
