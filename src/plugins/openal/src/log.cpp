#include "../log.hpp"
#include <sge/text.hpp>

sge::log::logger &sge::openal::log()
{
	static log::logger l(
		log::global(),
		SGE_TEXT("openal: "),
		true
	);
	return l;
}
