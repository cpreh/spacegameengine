#include <sge/thread/future/uninitialized.hpp>
#include <sge/text.hpp>

sge::thread::future::uninitialized::uninitialized()
:
	exception(
		SGE_TEXT("uninitialized"))
{
}
