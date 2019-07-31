//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/joypad/find_path.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/remove.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/remove.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


awl::event::optional_base_unique_ptr
sge::evdev::joypad::remove(
	sge::evdev::joypad::map &_map,
	boost::filesystem::path const &_path
)
{
	return
		fcppt::optional::map(
			sge::evdev::joypad::find_path(
				_map,
				_path
			),
			[
				&_map
			](
				sge::evdev::joypad::map::iterator const _pos
			)
			{
				sge::input::joypad::shared_ptr const result{
					_pos->second
				};

				_map.erase(
					_pos
				);

				return
					fcppt::unique_ptr_to_base<
						awl::event::base
					>(
						fcppt::make_unique_ptr<
							sge::input::joypad::event::remove
						>(
							result
						)
					);
			}
		);
}
