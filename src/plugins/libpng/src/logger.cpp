#include "../logger.hpp"
#include <sge/log/global.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
sge::libpng::logger()
{
	static fcppt::log::object local_log(
		fcppt::log::parameters::inherited(
			sge::log::global(),
			FCPPT_TEXT("libpng")));
	return local_log;
}
