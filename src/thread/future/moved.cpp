#include <sge/thread/future/moved.hpp>
#include <sge/text.hpp>

sge::thread::future::moved::moved()
:
	exception(
		SGE_TEXT("moved"))
{
}
