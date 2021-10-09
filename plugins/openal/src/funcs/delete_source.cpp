//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/exception.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/funcs/delete_source.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>

void sge::openal::funcs::delete_source(sge::openal::source_id const _source)
{
  ::alDeleteSources(fcppt::literal<ALsizei>(1), &_source.get());

  SGE_OPENAL_CHECK_STATE(FCPPT_TEXT("alDeleteSources failed"), sge::audio::exception)
}
