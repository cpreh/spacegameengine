//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/check_alc_state.hpp>
#include <sge/openal/funcs/alc_destroy_context.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <alc.h>
#include <fcppt/config/external_end.hpp>

void sge::openal::funcs::alc_destroy_context(ALCdevice &_device, ALCcontext &_context)
{
  ::alcDestroyContext(&_context);

  SGE_OPENAL_CHECK_ALC_STATE(_device, FCPPT_TEXT("alcDestroyContext failed"), sge::audio::exception)
}
