//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/joypad/find_path.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/optional_iterator.hpp>
#include <fcppt/const.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::evdev::joypad::optional_iterator
sge::evdev::joypad::find_path(
	sge::evdev::joypad::map &_map,
	std::filesystem::path const &_path
)
{
	// TODO: Make an algorithm for this
	sge::evdev::joypad::map::iterator const pos{
		std::find_if(
			_map.begin(),
			_map.end(),
			[
				&_path
			](
				sge::evdev::joypad::map::value_type const &_value
			)
			{
				return
					_value.second->path()
					==
					_path;
			}
		)
	};

	return
		fcppt::optional::make_if(
			pos
			!=
			_map.end(),
			fcppt::const_(
				pos
			)
		);
}
