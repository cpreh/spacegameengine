#include <sge/thread/future/already_retrieved.hpp>
#include <sge/text.hpp>

sge::thread::future::already_retrieved::already_retrieved()
:
	exception(
		SGE_TEXT("already retrieved"))
{
}
