//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/funcs/listener_float.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

void sge::openal::funcs::listener_float(ALenum const _what, ALfloat const _value)
{
  ::alListenerf(_what, _value);

  SGE_OPENAL_CHECK_STATE(FCPPT_TEXT("alListenerf failed"), sge::audio::exception)
}
