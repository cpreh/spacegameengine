//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/alc.hpp>
#include <sge/openal/check_alc_state.hpp>
#include <sge/openal/funcs/alc_make_context_current.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>

void sge::openal::funcs::alc_make_context_current(
    fcppt::reference<ALCdevice> const _device, ALCcontext *const _context)
{
  ::alcMakeContextCurrent(_context);

  SGE_OPENAL_CHECK_ALC_STATE(
      _device.get(), FCPPT_TEXT("alcMakeContextCurrent failed"), sge::audio::exception)
}
