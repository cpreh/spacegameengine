//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/funcs/doppler_factor.hpp>
#include <fcppt/text.hpp>

void sge::openal::funcs::doppler_factor(ALfloat const _value)
{
  ::alDopplerFactor(_value);

  SGE_OPENAL_CHECK_STATE(FCPPT_TEXT("alDopplerFactor failed"), sge::audio::exception)
}
