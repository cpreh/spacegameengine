//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/source_unqueue_buffers_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

void sge::openal::funcs::source_unqueue_buffers_impl(
    sge::openal::source_id const _source, ALsizei const _size, ALuint *const _result)
{
  ::alSourceUnqueueBuffers(_source.get(), _size, _result);

  SGE_OPENAL_CHECK_STATE(FCPPT_TEXT("alSourceUnqueueBuffers failed"), sge::audio::exception)
}
