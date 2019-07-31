//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/exception.hpp>
#include <sge/wlinput/xkb_context.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <fcppt/config/external_end.hpp>


sge::wlinput::xkb_context::xkb_context()
:
	context_{
		::xkb_context_new(
			XKB_CONTEXT_NO_FLAGS
		)
	}
{
	if(
		context_
		==
		nullptr
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("xkb_context_new failed")
			};
}

sge::wlinput::xkb_context::~xkb_context()
{
	::xkb_context_unref(
		context_
	);
}

::xkb_context *
sge::wlinput::xkb_context::get() const
{
	return
		context_;
}
