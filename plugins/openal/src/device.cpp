//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/openal/alc.hpp>
#include <sge/openal/device.hpp>
#include <sge/openal/funcs/alc_close_device.hpp>
#include <sge/openal/funcs/alc_open_device.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error_message.hpp>

sge::openal::device::device(ALCchar const *const _specifier)
    : device_(sge::openal::funcs::alc_open_device(_specifier))
{
}

ALCdevice &sge::openal::device::aldevice() { return *device_; }

sge::openal::device::~device()
{
  FCPPT_ASSERT_ERROR_MESSAGE(
      sge::openal::funcs::alc_close_device(this->aldevice()),
      FCPPT_TEXT("Error closing audio device. This means you tried to close the device before "
                 "unloading all contexts and buffers."));
}
