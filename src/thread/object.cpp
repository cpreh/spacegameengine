#include <sge/thread/object.hpp>

sge::thread::object::object(
	task const &_task)
:
	thread_(
		_task)
{
}
