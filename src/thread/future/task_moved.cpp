#include <sge/thread/future/task_moved.hpp>
#include <sge/text.hpp>

sge::thread::future::task_moved::task_moved()
:
	exception(
		SGE_TEXT("task moved"))
{
}
