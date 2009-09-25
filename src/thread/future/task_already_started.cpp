#include <sge/thread/future/task_already_started.hpp>
#include <sge/text.hpp>

sge::thread::future::task_already_started::task_already_started()
:
	exception(
		SGE_TEXT("task already started"))
{
}
