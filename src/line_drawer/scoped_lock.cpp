#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/line_drawer/object.hpp>

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
