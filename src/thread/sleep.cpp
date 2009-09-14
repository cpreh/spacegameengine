#include <sge/thread/sleep.hpp>
#include <boost/thread/thread.hpp>

void sge::thread::sleep(
	int const i)
{
	boost::this_thread::sleep(
		boost::posix_time::seconds(
			i));
}
