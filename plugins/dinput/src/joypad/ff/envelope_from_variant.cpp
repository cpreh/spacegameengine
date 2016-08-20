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


#include <sge/dinput/joypad/ff/convert_envelope.hpp>
#include <sge/dinput/joypad/ff/envelope_from_variant.hpp>
#include <sge/dinput/joypad/ff/optional_envelope.hpp>
#include <sge/input/joypad/ff/condition_fwd.hpp>
#include <sge/input/joypad/ff/constant.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/periodic.hpp>
#include <sge/input/joypad/ff/ramp.hpp>
#include <sge/input/joypad/ff/variant.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/variant/match.hpp>


sge::dinput::joypad::ff::optional_envelope
sge::dinput::joypad::ff::envelope_from_variant(
	sge::input::joypad::ff::variant const &_variant
)
{
	typedef
	fcppt::optional::object<
		sge::input::joypad::ff::envelope
	>
	result_type;

	return
		fcppt::optional::map(
			fcppt::variant::match(
				_variant,
				[](
					sge::input::joypad::ff::constant const &_constant
				)
				{
					return
						result_type{
							_constant.envelope()
						};
				},
				[](
					sge::input::joypad::ff::ramp const &_ramp
				)
				{
					return
						result_type{
							_ramp.envelope()
						};
				},
				[](
					sge::input::joypad::ff::periodic const &_periodic
				)
				{
					return
						result_type{
							_periodic.envelope()
						};
				},
				[](
					sge::input::joypad::ff::condition const &
				)
				{
					return
						result_type{};
				}
			),
			[](
				sge::input::joypad::ff::envelope const &_envelope
			)
			{
				return
					sge::dinput::joypad::ff::convert_envelope(
						_envelope
					);
			}
		);

}
