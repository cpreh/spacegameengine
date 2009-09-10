#include <sge/thread/object.hpp>

sge::thread::object::object(
	task const &_task)
:
	thread_(
		_task)
{
}

void sge::thread::object::join()
{
	thread_.join();
}

sge::thread::object::~object()
{
	if (thread_.joinable())
		std::terminate();
}
