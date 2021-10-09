//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_KEYBOARD_ENUMERATOR_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_ENUMERATOR_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/keyboard/key_map.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace dinput
{
namespace keyboard
{

class enumerator : public sge::dinput::device::enumerator
{
  FCPPT_NONCOPYABLE(enumerator);

public:
  enumerator();

  ~enumerator() override;

  sge::dinput::keyboard::key_map const &key_map() const;

private:
  void dispatch(DIDEVICEOBJECTINSTANCE const &) override;

  sge::dinput::keyboard::key_map key_map_;
};

}
}
}

#endif
