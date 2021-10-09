//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/source_pause.hpp>
#include <fcppt/text.hpp>

void sge::openal::funcs::source_pause(sge::openal::source_id const _id)
{
  ::alSourcePause(_id.get());

  SGE_OPENAL_CHECK_STATE(FCPPT_TEXT("alSourcePause failed"), sge::audio::exception)
}
