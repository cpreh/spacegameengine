//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/exception.hpp>
#include <sge/cg/parameter/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


sge::cg::parameter::object::object(
	CGparameter const _parameter // NOLINT(misc-misplaced-const)
)
:
	parameter_(
		_parameter
	)
{
	if(
		parameter_
		==
		nullptr
	)
	{
		throw
			sge::cg::exception{
				FCPPT_TEXT("Parameter is null.")
			};
	}
}

CGparameter
sge::cg::parameter::object::get() const
{
	return
		parameter_;
}
