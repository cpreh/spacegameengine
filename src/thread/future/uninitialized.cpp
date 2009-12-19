#include <sge/thread/future/uninitialized.hpp>
#include <fcppt/text.hpp>

sge::thread::future::uninitialized::uninitialized()
:
	exception(
		FCPPT_TEXT("uninitialized"))
{
}
