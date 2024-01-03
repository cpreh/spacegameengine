//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_CHECK_STATE_LISTING_HPP_INCLUDED
#define SGE_CG_CHECK_STATE_LISTING_HPP_INCLUDED

#include <sge/cg/check_state.hpp>
#include <sge/cg/error_listing.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>

#define SGE_CG_CHECK_STATE_LISTING(context, message, exception) \
  SGE_CG_CHECK_STATE(message + FCPPT_TEXT(":\n") + sge::cg::error_listing(context), exception)

#endif
