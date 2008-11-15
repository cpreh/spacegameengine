#include "../log.hpp"
#include <sge/text.hpp>

sge::log::logger &sge::mad::log()
{
	static log::logger l(
		log::global(),
		SGE_TEXT("mad: "));
	return l;
}
