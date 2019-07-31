//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>


sge::line_drawer::scoped_lock::scoped_lock(
	object &_object)
:
	object_(
		_object)
{
	object_.lock();
}

sge::line_drawer::line_sequence &
sge::line_drawer::scoped_lock::value() const
{
	return object_.lines_;
}

sge::line_drawer::scoped_lock::~scoped_lock()
{
	object_.unlock();
}
