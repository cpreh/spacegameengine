//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/profile/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


sge::cg::profile::object::object(
	CGprofile const _profile
)
:
	profile_(
		_profile
	)
{
}

CGprofile
sge::cg::profile::object::get() const
{
	return
		profile_;
}
