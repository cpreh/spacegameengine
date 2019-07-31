//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/sdlinput/same_windows_impl.hpp>
#include <awl/backends/sdl/window/from_id.hpp>
#include <awl/backends/sdl/window/object.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


bool
sge::sdlinput::same_windows_impl(
	awl::backends::sdl::window::object const &_window,
	std::uint32_t const _id
)
{
	return
		fcppt::optional::maybe(
			awl::backends::sdl::window::from_id(
				_id
			),
			fcppt::const_(
				false
			),
			[
				&_window
			](
				fcppt::reference<
					SDL_Window
				> const _other
			)
			{
				return
					&_other.get()
					==
					&_window.get();
			}
		);
}
