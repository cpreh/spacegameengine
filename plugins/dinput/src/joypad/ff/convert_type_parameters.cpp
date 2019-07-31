//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/joypad/ff/convert_condition.hpp>
#include <sge/dinput/joypad/ff/convert_constant.hpp>
#include <sge/dinput/joypad/ff/convert_periodic.hpp>
#include <sge/dinput/joypad/ff/convert_ramp.hpp>
#include <sge/dinput/joypad/ff/convert_type_parameters.hpp>
#include <sge/dinput/joypad/ff/type_parameters.hpp>
#include <sge/input/joypad/ff/condition_fwd.hpp>
#include <sge/input/joypad/ff/constant_fwd.hpp>
#include <sge/input/joypad/ff/periodic_fwd.hpp>
#include <sge/input/joypad/ff/ramp_fwd.hpp>
#include <sge/input/joypad/ff/variant.hpp>
#include <fcppt/variant/match.hpp>


sge::dinput::joypad::ff::type_parameters
sge::dinput::joypad::ff::convert_type_parameters(
	sge::input::joypad::ff::variant const &_variant
)
{
	return
		fcppt::variant::match(
			_variant,
			[](
				sge::input::joypad::ff::constant const &_constant
			)
			{
				return
					sge::dinput::joypad::ff::type_parameters{
						sge::dinput::joypad::ff::convert_constant(
							_constant
						)
					};
			},
			[](
				sge::input::joypad::ff::ramp const &_ramp
			)
			{
				return
					sge::dinput::joypad::ff::type_parameters{
						sge::dinput::joypad::ff::convert_ramp(
							_ramp
						)
					};
			},
			[](
				sge::input::joypad::ff::periodic const &_periodic
			)
			{
				return
					sge::dinput::joypad::ff::type_parameters{
						sge::dinput::joypad::ff::convert_periodic(
							_periodic
						)
					};
			},
			[](
				sge::input::joypad::ff::condition const &_condition
			)
			{
				return
					sge::dinput::joypad::ff::type_parameters{
						sge::dinput::joypad::ff::convert_condition(
							_condition
						)
					};
			}
		);
}
