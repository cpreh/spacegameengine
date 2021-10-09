//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/source_int.hpp>
#include <fcppt/text.hpp>

void sge::openal::funcs::source_int(
    sge::openal::source_id const _source, ALenum const _what, ALint const _value)
{
  ::alSourcei(_source.get(), _what, _value);

  SGE_OPENAL_CHECK_STATE(FCPPT_TEXT("alSourcei failed"), sge::audio::exception)
}
