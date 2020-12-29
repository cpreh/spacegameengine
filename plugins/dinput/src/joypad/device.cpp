//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/is_down.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/device.hpp>
#include <sge/dinput/joypad/make_info.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/dinput/joypad/ff/effect.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/button_id.hpp>
#include <sge/input/joypad/button_pressed.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/relative_axis_id.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/absolute_axis.hpp>
#include <sge/input/joypad/event/button.hpp>
#include <sge/input/joypad/event/relative_axis.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/alternative.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::dinput::joypad::device::device(
	sge::dinput::device::parameters const &_parameters,
	sge::input::info::name const &_name
)
:
	sge::input::joypad::device{},
	sge::dinput::device::object(
		_parameters,
		c_dfDIJoystick2
	),
	fcppt::enable_shared_from_this<
		sge::dinput::joypad::device
	>{},
	info_(
		sge::dinput::joypad::make_info(
			this->get(),
			_name,
			_parameters.guid()
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::dinput::joypad::device::~device()
{
}

sge::window::object &
sge::dinput::joypad::device::window() const
{
	return
		this->sge_window();
}

sge::input::joypad::info const &
sge::dinput::joypad::device::info() const
{
	return
		info_.input_info();
}

sge::input::joypad::ff::effect_unique_ptr
sge::dinput::joypad::device::create_ff_effect(
	sge::input::joypad::ff::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::input::joypad::ff::effect
		>(
			fcppt::make_unique_ptr<
				sge::dinput::joypad::ff::effect
			>(
				this->get(),
				info_.button_map(),
				_parameters
			)
		);
}

awl::event::optional_base_unique_ptr
sge::dinput::joypad::device::on_dispatch(
	DIDEVICEOBJECTDATA const &_data
)
{
	auto const absolute_axis_event(
		[
			&_data,
			this
		](
			sge::input::joypad::absolute_axis_id const _id
		)
		->
		awl::event::base_unique_ptr
		{
			return
				fcppt::unique_ptr_to_base<
					awl::event::base
				>(
					fcppt::make_unique_ptr<
						sge::input::joypad::event::absolute_axis
					>(
						sge::input::joypad::shared_ptr{
							this->fcppt_shared_from_this()
						},
						sge::input::joypad::absolute_axis(
							FCPPT_ASSSERT_OPTIONAL_ERROR(
								this->info_.input_info().absolute_axes()[
									_id
								]
							)->code(),
							_id
						),
						// TODO: Conversion function
						static_cast<
							sge::input::joypad::axis_value
						>(
							_data.dwData
						)
					)
				);
		}
	);

	auto const button_event(
		[
			this,
			&_data
		](
			sge::input::joypad::button_id const _id
		)
		->
		awl::event::base_unique_ptr
		{
			return
				fcppt::unique_ptr_to_base<
					awl::event::base
				>(
					fcppt::make_unique_ptr<
						sge::input::joypad::event::button
					>(
						sge::input::joypad::shared_ptr{
							this->fcppt_shared_from_this()
						},
						_id,
						sge::input::joypad::button_pressed{
							sge::dinput::is_down(
								_data.dwData
							)
						}
					)
				);
		}
	);

	auto const relative_axis_event(
		[
			this,
			&_data
		](
			sge::input::joypad::relative_axis_id const _id
		)
		->
		awl::event::base_unique_ptr
		{
			return
				fcppt::unique_ptr_to_base<
					awl::event::base
				>(
					fcppt::make_unique_ptr<
						sge::input::joypad::event::relative_axis
					>(
						sge::input::joypad::shared_ptr{
							this->fcppt_shared_from_this()
						},
						sge::input::joypad::relative_axis(
							FCPPT_ASSSERT_OPTIONAL_ERROR(
								info_.input_info().relative_axes()[
									_id
								]
							)->code(),
							_id
						),
						// TODO: Conversion function
						static_cast<
							sge::input::joypad::axis_value
						>(
							_data.dwData
						)
					)
				);
		}
	);

	return
		fcppt::optional::alternative(
			fcppt::optional::map(
				fcppt::optional::copy_value(
					fcppt::container::find_opt_mapped(
						this->info_.absolute_axis_map(),
						_data.dwOfs
					)
				),
				absolute_axis_event
			),
			[
				&button_event,
				&relative_axis_event,
				&_data,
				this
			]{
				return
					fcppt::optional::alternative(
						fcppt::optional::map(
							fcppt::optional::copy_value(
								fcppt::container::find_opt_mapped(
									this->info_.button_map(),
									_data.dwOfs
								)
							),
							button_event
						),
						[
							&relative_axis_event,
							&_data,
							this
						]{
							return
								fcppt::optional::map(
									fcppt::optional::copy_value(
										fcppt::container::find_opt_mapped(
											this->info_.relative_axis_map(),
											_data.dwOfs
										)
									),
									relative_axis_event
								);
						}
					);
			}
		);
}
