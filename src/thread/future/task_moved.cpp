#include <sge/thread/future/task_moved.hpp>
#include <fcppt/text.hpp>

sge::thread::future::task_moved::task_moved()
:
	exception(
		FCPPT_TEXT("task moved"))
{
}
