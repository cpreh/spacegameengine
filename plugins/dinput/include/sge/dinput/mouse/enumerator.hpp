//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_MOUSE_ENUMERATOR_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_ENUMERATOR_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace dinput
{
namespace mouse
{

class enumerator : public sge::dinput::device::enumerator
{
  FCPPT_NONCOPYABLE(enumerator);

public:
  enumerator();

  ~enumerator() override;

  sge::input::mouse::axis_info_container::vector const &axis() const;

  sge::input::mouse::button_info_container::vector const &buttons() const;

  sge::dinput::mouse::axis_map const &axis_map() const;

  sge::dinput::mouse::button_map const &button_map() const;

private:
  void dispatch(DIDEVICEOBJECTINSTANCE const &) override;

  sge::input::mouse::axis_info_container::vector axis_;

  sge::input::mouse::button_info_container::vector buttons_;

  sge::dinput::mouse::axis_map axis_map_;

  sge::dinput::mouse::button_map button_map_;
};

}
}
}

#endif
