#include <sge/collision/group_overflow.hpp>
#include <sge/text.hpp>

sge::collision::group_overflow::group_overflow()
:
	exception(
		SGE_TEXT("There are no more groups identifiers available"))
{
}