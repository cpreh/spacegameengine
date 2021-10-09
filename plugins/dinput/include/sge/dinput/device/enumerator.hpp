//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_DEVICE_ENUMERATOR_HPP_INCLUDED
#define SGE_DINPUT_DEVICE_ENUMERATOR_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace dinput
{
namespace device
{

class enumerator
{
  FCPPT_NONCOPYABLE(enumerator);

protected:
  enumerator();

public:
  virtual ~enumerator() = 0;

  virtual void dispatch(DIDEVICEOBJECTINSTANCE const &) = 0;
};

}
}
}

#endif
