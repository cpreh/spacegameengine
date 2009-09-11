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
	sge::cerr << "sleeping...\n";
	boost::this_thread::sleep(
		boost::posix_time::seconds(3)); 
	sge::cerr << "woke up!\n";
	return true;
}

void void_task()
{
	sge::cerr << "sleeping in void\n";
	boost::this_thread::sleep(
		boost::posix_time::seconds(4)); 
	sge::cerr << "void woke up\n";
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
		sge::cerr << "waiting\n";
	sge::cerr << "finished! result: " << result << "\n";
	sge::cerr << "get again: " << future_.get() << "\n";
	sge::cerr << "state is: " << static_cast<int>(future_.state()) << "\n";
	sge::cerr << "is_ready: " << future_.is_ready() << ", has_exception: " << future_.has_exception() << ", has_value: " << future_.has_value() << ", was_moved: " << future_.was_moved() << "\n";
	thread_.join();
		/*
	sge::thread::future::packaged_task<void> void_task_(
		&void_task);
	sge::thread::future::shared_object<void> void_future_(
		void_task_.object());
	sge::thread::object void_thread_(
		boost::ref(
			void_task_));
	sge::cerr << "thread erstellt\n";
	sge::cerr << "state is: " << static_cast<int>(void_future_.state()) << "\n";
	sge::cerr << "is_ready: " << void_future_.is_ready() << ", has_exception: " << void_future_.has_exception() << ", has_value: " << void_future_.has_value() << ", was_moved: " << void_future_.was_moved() << "\n";
	sge::cerr << "warte, bis er fertig ist\n";
	void_future_.wait();
	void_thread_.join();*/
}
