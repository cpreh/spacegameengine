/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
