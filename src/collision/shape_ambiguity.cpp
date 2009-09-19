#include <sge/collision/shape_ambiguity.hpp>
#include <sge/text.hpp>

sge::collision::shape_ambiguity::shape_ambiguity()
:
	exception(
		SGE_TEXT("Tried to assign a shape to multiple bodies, which is invalid"))
{
}