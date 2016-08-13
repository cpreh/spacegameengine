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


#include <sge/evdev/joypad/ff/convert_condition.hpp>
#include <sge/evdev/joypad/ff/convert_constant.hpp>
#include <sge/evdev/joypad/ff/convert_periodic.hpp>
#include <sge/evdev/joypad/ff/convert_ramp.hpp>
#include <sge/evdev/joypad/ff/convert_variant.hpp>
#include <sge/evdev/joypad/ff/variant.hpp>
#include <sge/input/joypad/ff/condition_fwd.hpp>
#include <sge/input/joypad/ff/constant_fwd.hpp>
#include <sge/input/joypad/ff/periodic_fwd.hpp>
#include <sge/input/joypad/ff/ramp_fwd.hpp>
#include <sge/input/joypad/ff/variant.hpp>
#include <fcppt/variant/match.hpp>


sge::evdev::joypad::ff::variant
sge::evdev::joypad::ff::convert_variant(
	sge::input::joypad::ff::variant const &_variant
)
{
	sge::evdev::joypad::ff::variant result;

	fcppt::variant::match(
		_variant,
		[
			&result
		](
			sge::input::joypad::ff::constant const &_constant
		)
		{
			result.constant =
				sge::evdev::joypad::ff::convert_constant(
					_constant
				);
		},
		[
			&result
		](
			sge::input::joypad::ff::ramp const &_ramp
		)
		{
			result.ramp =
				sge::evdev::joypad::ff::convert_ramp(
					_ramp
				);
		},
		[
			&result
		](
			sge::input::joypad::ff::periodic const &_periodic
		)
		{
			result.periodic =
				sge::evdev::joypad::ff::convert_periodic(
					_periodic
				);
		},
		[
			&result
		](
			sge::input::joypad::ff::condition const &_condition
		)
		{
			// TODO: Should we separate this?

			ff_condition_effect const effect(
				sge::evdev::joypad::ff::convert_condition(
					_condition
				)
			);

			result.condition[
				0
			] =
				effect;

			result.condition[
				1
			] =
				effect;
		}
	);

	return
		result;
}
