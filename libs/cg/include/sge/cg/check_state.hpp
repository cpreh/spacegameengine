//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_CHECK_STATE_HPP_INCLUDED
#define SGE_CG_CHECK_STATE_HPP_INCLUDED

#include <sge/cg/error_string.hpp> // IWYU pragma: keep
#include <sge/core/check_state.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

#define SGE_CG_CHECK_STATE(message, exception) \
  SGE_CORE_CHECK_STATE( \
      exception, message, CGerror, ::cgGetError(), CG_NO_ERROR, sge::cg::error_string)

#endif
