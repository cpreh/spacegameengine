//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/check_state.hpp>
#include <sge/cg/error_listing.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/context/object.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


fcppt::string
sge::cg::error_listing(
	sge::cg::context::object const &_context
)
{
	char const *const ret(
		::cgGetLastListing(
			_context.get()
		)
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgGetLastListing failed"),
		sge::cg::exception
	)

	return
		ret
		==
		nullptr
		?
			fcppt::string()
		:
			fcppt::from_std_string(
				ret
			)
		;
}
