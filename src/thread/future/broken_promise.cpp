#include <sge/thread/future/broken_promise.hpp>
#include <sge/text.hpp>

sge::thread::future::broken_promise::broken_promise()
:
	exception(
		SGE_TEXT("broken promise"))
{
}
