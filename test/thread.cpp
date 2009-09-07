#include <sge/thread/future/packaged_task.hpp>
#include <sge/thread/future/promise.hpp>
#include <sge/thread/object.hpp>

namespace
{
bool task()
{
	return true;
}
}

int main()
{
	sge::thread::future::packaged_task<bool> task_(
		&task);
	sge::thread::future::unique_object<bool> future_ = 
		task_.get_future();
	sge::thread::object thread_(
		boost::ref(task_));
	future_.wait();

}
