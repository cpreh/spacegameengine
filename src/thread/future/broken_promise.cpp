#include <sge/thread/future/broken_promise.hpp>
#include <sge/text.hpp>

sge::thread::future::broken_promise::broken_promise()
:
	exception(
		FCPPT_TEXT("broken promise"))
{
}
