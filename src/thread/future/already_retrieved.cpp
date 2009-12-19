#include <sge/thread/future/already_retrieved.hpp>
#include <fcppt/text.hpp>

sge::thread::future::already_retrieved::already_retrieved()
:
	exception(
		FCPPT_TEXT("already retrieved"))
{
}
