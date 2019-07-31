//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/exception.hpp>
#include <sge/cg/context/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


sge::cg::context::object::object()
:
	context_(
		::cgCreateContext()
	)
{
	if(
		context_
		==
		nullptr
	)
		throw sge::cg::exception(
			FCPPT_TEXT("cgCreateContext failed")
		);
}

sge::cg::context::object::~object()
{
	::cgDestroyContext(
		context_
	);
}

CGcontext
sge::cg::context::object::get() const
{
	return context_;
}
