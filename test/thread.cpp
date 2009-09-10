#include <sge/thread/future/packaged_task.hpp>
#include <sge/thread/future/shared_object.hpp>
#include <sge/thread/object.hpp>
#include <sge/cerr.hpp>
#include <sge/time/sleep.hpp>
#include <sge/time/second.hpp>

namespace
{
bool task()
{
	sge::cerr << "schlafe\n";
	//sge::time::sleep(sge::time::second(2));
	boost::this_thread::sleep(
		boost::posix_time::seconds(3)); 
	sge::cerr << "aufgewacht!\n";
	return true;
}
}

int main()
{
	sge::thread::future::packaged_task<bool> task_(
		&task);
	sge::thread::future::shared_object<bool> future_(
		task_.object());
	sge::cerr << "created future\n";
	sge::thread::object thread_(
		boost::ref(
			task_));
	sge::cerr << "created thread, waiting now\n";
	bool result;
	while (!future_.try_get(result))
		sge::cerr << "warte\n";
	sge::cerr << "fertig! ergebis: " << result << "\n";
	thread_.join();
}
