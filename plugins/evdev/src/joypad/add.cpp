//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/create.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp>
#include <sge/evdev/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/discover.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/posix/processor_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


awl::event::optional_base_unique_ptr
sge::evdev::joypad::add(
	fcppt::log::object &_log,
	sge::window::object &_window,
	awl::backends::posix::processor &_processor,
	sge::evdev::joypad::map &_map,
	std::filesystem::path const &_path
)
{
	return
		fcppt::optional::map(
			sge::evdev::joypad::create(
				_log,
				_window,
				_processor,
				_path
			),
			[
				&_map
			](
				sge::evdev::joypad::shared_ptr const _ptr
			)
			{
				FCPPT_ASSERT_ERROR(
					_map.insert(
						std::make_pair(
							_ptr->posix_fd(),
							_ptr
						)
					).second
				);

				return
					fcppt::unique_ptr_to_base<
						awl::event::base
					>(
						fcppt::make_unique_ptr<
							sge::input::joypad::event::discover
						>(
							_ptr
						)
					);
			}
		);
}
