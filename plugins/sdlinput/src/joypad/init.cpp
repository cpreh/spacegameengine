//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/device_id.hpp>
#include <sge/sdlinput/joypad/init.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <vector>
#include <fcppt/config/external_end.hpp>

std::vector<sge::sdlinput::joypad::shared_ptr>
sge::sdlinput::joypad::init(sge::window::object_ref const _window, fcppt::log::object &_log)
{
  return fcppt::algorithm::map_optional<std::vector<sge::sdlinput::joypad::shared_ptr>>(
      fcppt::make_int_range_count(SDL_NumJoysticks()),
      [&_window, &_log](int const _index)
      {
        using result_type = fcppt::optional::object<sge::sdlinput::joypad::shared_ptr>;

        try
        {
          return result_type{fcppt::make_shared_ptr<sge::sdlinput::joypad::device>(
              _window, sge::sdlinput::joypad::device_id{_index})};
        }
        catch (sge::input::exception const &_error)
        {
          FCPPT_LOG_ERROR(
              _log,
              fcppt::log::out << FCPPT_TEXT("Unable to initialize an SDL joystick: ")
                              << _error.string())

          return result_type{};
        }
      });
}
