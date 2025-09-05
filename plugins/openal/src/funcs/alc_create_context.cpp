//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/check_alc_state.hpp>
#include <sge/openal/funcs/alc_create_context.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <alc.h>
#include <fcppt/config/external_end.hpp>

ALCcontext *sge::openal::funcs::alc_create_context(fcppt::reference<ALCdevice> const _device)
{
  fcppt::array::object<ALCint, 1U> const attributes{0};

  // NOLINTNEXTLINE(misc-const-correctness)
  ALCcontext *const result(::alcCreateContext(&_device.get(), attributes.data()));

  SGE_OPENAL_CHECK_ALC_STATE(
      _device.get(), FCPPT_TEXT("alcCreateContext failed"), sge::audio::exception)

  if (result == nullptr)
  {
    throw sge::audio::exception{FCPPT_TEXT("AL context is null")};
  }

  return result;
}
