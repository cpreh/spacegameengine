//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/device.hpp>
#include <sge/openal/funcs/alc_close_device.hpp>
#include <sge/openal/funcs/alc_open_device.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <alc.h>
#include <exception>
#include <fcppt/config/external_end.hpp>

sge::openal::device::device(ALCchar const *const _specifier)
    : device_(sge::openal::funcs::alc_open_device(_specifier))
{
}

ALCdevice &sge::openal::device::aldevice() { return *device_; }

sge::openal::device::~device()
{
  if (fcppt::not_(sge::openal::funcs::alc_close_device(this->aldevice())))
  {
    std::terminate();
  }
}
