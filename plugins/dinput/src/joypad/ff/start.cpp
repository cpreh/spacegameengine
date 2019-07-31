//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/start.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/ff/optional_play_count.hpp>
#include <sge/input/joypad/ff/play_count.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::dinput::joypad::ff::start(
	IDirectInputEffect &_effect,
	sge::input::joypad::ff::optional_play_count const &_opt_count
)
{
	if(
		_effect.Start(
			fcppt::optional::maybe(
				_opt_count,
				fcppt::const_<
					DWORD
				>(
					INFINITE
				),
				[](
					sge::input::joypad::ff::play_count const _count
				)
				{
					return
						fcppt::cast::size<
							DWORD
						>(
							_count.get()
						);
				}
			),
			DIES_NODOWNLOAD
		)
		!=
		DI_OK
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("Starting effect failed")
			};
}
