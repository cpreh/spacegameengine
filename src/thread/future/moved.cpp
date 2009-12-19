#include <sge/thread/future/moved.hpp>
#include <fcppt/text.hpp>

sge::thread::future::moved::moved()
:
	exception(
		FCPPT_TEXT("moved"))
{
}
