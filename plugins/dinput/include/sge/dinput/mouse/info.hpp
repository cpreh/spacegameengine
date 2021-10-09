//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_MOUSE_INFO_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_INFO_HPP_INCLUDED

#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/dinput/mouse/info_fwd.hpp>
#include <sge/input/mouse/info.hpp>

namespace sge
{
namespace dinput
{
namespace mouse
{

class info
{
public:
  info(
      sge::input::mouse::info const &,
      sge::dinput::mouse::axis_map const &,
      sge::dinput::mouse::button_map const &);

  sge::input::mouse::info const &input_info() const;

  sge::dinput::mouse::axis_map const &axis_map() const;

  sge::dinput::mouse::button_map const &button_map() const;

private:
  sge::input::mouse::info input_info_;

  sge::dinput::mouse::axis_map axis_map_;

  sge::dinput::mouse::button_map button_map_;
};

}
}
}

#endif
