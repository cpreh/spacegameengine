//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
