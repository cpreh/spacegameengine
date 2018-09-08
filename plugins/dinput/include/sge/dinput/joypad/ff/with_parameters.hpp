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


#ifndef SGE_DINPUT_JOYPAD_FF_WITH_PARAMETERS_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_FF_WITH_PARAMETERS_HPP_INCLUDED

#include <sge/dinput/cast_key.hpp>
#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/ff/convert_duration.hpp>
#include <sge/dinput/joypad/ff/convert_type_parameters.hpp>
#include <sge/dinput/joypad/ff/envelope_from_variant.hpp>
#include <sge/dinput/joypad/ff/optional_envelope.hpp>
#include <sge/dinput/joypad/ff/type_parameters.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/ff/degrees_value.hpp>
#include <sge/input/joypad/ff/duration.hpp>
#include <sge/input/joypad/ff/parameters.hpp>
#include <sge/input/joypad/ff/periodic.hpp>
#include <sge/input/joypad/ff/trigger.hpp>
#include <fcppt/const.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/optional/to_pointer.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{
namespace ff
{

template<
	typename Result
>
Result
with_parameters(
	sge::dinput::joypad::button_map const &_button_map,
	sge::input::joypad::ff::parameters const &_parameters,
	fcppt::function<
		Result (
			DIEFFECT const &
		)
	> const _function
)
{
	// TODO: How many axes do we want? evdev can do two.
	std::array<
		DWORD,
		1
	> axes{{
		// TODO: Is this right?
		fcppt::literal<
			DWORD
		>(
			sge:: dinput::cast_key(
				DIMOFS_Z
			)
		)
	}};

	std::array<
		LONG,
		1
	> direction{{
		fcppt::cast::size<
			LONG
		>(
			// We need hundredths of degrees here
			_parameters.direction().get().get()
			/
			fcppt::literal<
				sge::input::joypad::ff::degrees_value
			>(
				10
			)
		)
	}};

	sge::dinput::joypad::ff::optional_envelope envelope{
		sge::dinput::joypad::ff::envelope_from_variant(
			_parameters.variant()
		)
	};

	sge::dinput::joypad::ff::type_parameters variant_parameters{
		sge::dinput::joypad::ff::convert_type_parameters(
			_parameters.variant()
		)
	};

	DIEFFECT const effect{
		sizeof(
			DIEFFECT
		),
		DIEFF_OBJECTOFFSETS
		|
		DIEFF_SPHERICAL,
		fcppt::optional::maybe(
			_parameters.duration(),
			fcppt::const_<
				DWORD
			>(
				INFINITE
			),
			[](
				sge::input::joypad::ff::duration const _duration
			)
			{
				return
					sge::dinput::joypad::ff::convert_duration(
						_duration
					);
			}
		),
		fcppt::optional::maybe(
			fcppt::variant::to_optional<
				sge::input::joypad::ff::periodic
			>(
				_parameters.variant()
			),
			fcppt::const_<
				DWORD
			>(
				0u
			),
			[](
				sge::input::joypad::ff::periodic const &_periodic
			)
			{
				return
					sge::dinput::joypad::ff::convert_duration(
						_periodic.period().get()
					);
			}
		),
		// TODO: What should the gain be?
		fcppt::literal<
			DWORD
		>(
			1
		),
		fcppt::optional::maybe(
			_parameters.trigger(),
			fcppt::const_<
				DWORD
			>(
				DIEB_NOTRIGGER
			),
			[
				&_button_map
			](
				sge::input::joypad::ff::trigger const &_trigger
			)
			{
				// TODO: Use a bimap?
				return
					fcppt::optional::to_exception(
						fcppt::optional::deref(
							fcppt::algorithm::find_if_opt(
								_button_map,
								[
									&_trigger
								](
									std::pair<
										DWORD,
										sge::input::joypad::button_id
									> const _pair
								)
								{
									return
										_pair.second
										==
										_trigger.button();
								}
							)
						),
						[
							&_trigger
						]{
							return
								sge::input::exception{
									FCPPT_TEXT("Invalid button id for FF effect!")
									+
									fcppt::output_to_fcppt_string(
										_trigger.button()
									)
								};
						}
					).get().first;
			}
		),
		fcppt::optional::from(
			fcppt::optional::bind(
				_parameters.trigger(),
				[](
					sge::input::joypad::ff::trigger const &_trigger
				)
				{
					return
						fcppt::optional::map(
							_trigger.cooldown().get(),
							[](
								sge::input::joypad::ff::duration const _duration
							)
							{
								return
									sge::dinput::joypad::ff::convert_duration(
										_duration
									);
							}
						);
				}
			),
			fcppt::const_<
				DWORD
			>(
				INFINITE
			)
		),
		fcppt::cast::size<
			DWORD
		>(
			axes.size()
		),
		axes.data(),
		direction.data(),
		fcppt::optional::to_pointer(
			fcppt::optional::map(
				envelope,
				[](
					DIENVELOPE &_envelope
				)
				{
					return
						fcppt::make_ref(
							_envelope
						);
				}
			)
		),
		fcppt::variant::apply(
			[](
				auto const &_value
			)
			{
				return
					fcppt::cast::size<
						DWORD
					>(
						sizeof(
							_value
						)
					);
			},
			variant_parameters
		),
		fcppt::variant::apply(
			[](
				auto &_value
			)
			->
			void *
			{
				return
					&_value;
			},
			variant_parameters
		),
		sge::dinput::joypad::ff::convert_duration(
			_parameters.delay().get()
		)
	};

	return
		_function(
			effect
		);
}

}
}
}
}

#endif
