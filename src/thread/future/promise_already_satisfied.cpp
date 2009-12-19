#include <sge/thread/future/promise_already_satisfied.hpp>
#include <fcppt/text.hpp>

sge::thread::future::promise_already_satisfied::promise_already_satisfied()
:
	exception(
		FCPPT_TEXT("promise already satisfied"))
{
}
