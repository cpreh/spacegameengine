//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENAL_CHECK_STATE_HPP_INCLUDED
#define SGE_OPENAL_CHECK_STATE_HPP_INCLUDED

#include <sge/core/check_state.hpp>
#include <sge/openal/error_string.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <al.h>
#include <fcppt/config/external_end.hpp>

#define SGE_OPENAL_CHECK_STATE(message, exception) \
  SGE_CORE_CHECK_STATE( \
      exception, message, ALenum, ::alGetError(), AL_NO_ERROR, sge::openal::error_string)

#endif
