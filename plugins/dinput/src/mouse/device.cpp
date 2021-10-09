//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/is_down.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/dinput/mouse/device.hpp>
#include <sge/dinput/mouse/make_info.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/axis_id.hpp>
#include <sge/input/mouse/axis_value.hpp>
#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info_fwd.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/input/mouse/event/button.hpp>
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

sge::dinput::mouse::device::device(
    sge::dinput::device::parameters const &_parameters, sge::input::info::name const &_name)
    : sge::input::mouse::device{},
      sge::dinput::device::object{_parameters, c_dfDIMouse2},
      fcppt::enable_shared_from_this<sge::dinput::mouse::device>{},
      info_{sge::dinput::mouse::make_info(this->get(), _name)}
{
}

FCPPT_PP_POP_WARNING

sge::dinput::mouse::device::~device() {}

sge::window::object &sge::dinput::mouse::device::window() const { return this->sge_window(); }

sge::input::mouse::info const &sge::dinput::mouse::device::info() const
{
  return info_.input_info();
}

awl::event::optional_base_unique_ptr
sge::dinput::mouse::device::on_dispatch(DIDEVICEOBJECTDATA const &_data)
{
  auto const axis_event(
      [&_data, this](sge::input::mouse::axis_id const _id) -> awl::event::base_unique_ptr
      {
        return fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::mouse::event::axis>(
                sge::input::mouse::shared_ptr{this->fcppt_shared_from_this()},
                sge::input::mouse::axis(
                    FCPPT_ASSERT_OPTIONAL_ERROR(info_.input_info().axes()[_id])->code(), _id),
                // TODO: Conversion function
                static_cast<sge::input::mouse::axis_value>(_data.dwData)));
      });

  auto const button_event(
      [&_data, this](sge::input::mouse::button_id const _id) -> awl::event::base_unique_ptr
      {
        return fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::mouse::event::button>(
                sge::input::mouse::shared_ptr{this->fcppt_shared_from_this()},
                sge::input::mouse::button(
                    FCPPT_ASSERT_OPTIONAL_ERROR(info_.input_info().buttons()[_id])->code(), _id),
                sge::input::mouse::button_pressed{sge::dinput::is_down(_data.dwData)}));
      });

  return fcppt::optional::alternative(
      fcppt::optional::map(
          fcppt::optional::copy_value(
              fcppt::container::find_opt_mapped(info_.axis_map(), _data.dwOfs)),
          [&axis_event, this, &_data](sge::input::mouse::axis_id const _id)
          { return axis_event(_id); }),
      [&_data, &button_event, this]
      {
        return fcppt::optional::map(
            fcppt::optional::copy_value(
                fcppt::container::find_opt_mapped(info_.button_map(), _data.dwOfs)),
            [&button_event, this, &_data](sge::input::mouse::button_id const _id)
            { return button_event(_id); });
      });
}
