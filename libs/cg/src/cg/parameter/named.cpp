//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/parameter/named.hpp>
#include <sge/cg/parameter/object.hpp>


sge::cg::parameter::named::named(
	sge::cg::parameter::object const &_impl
)
:
	impl_(
		_impl
	)
{
}

sge::cg::parameter::object const &
sge::cg::parameter::named::object() const
{
	return
		impl_;
}
