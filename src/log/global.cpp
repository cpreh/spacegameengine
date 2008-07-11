#include <sge/log/global.hpp>
#include <sge/log/logger.hpp>
#include <sge/log/level.hpp>
#include <sge/iostream.hpp>
#include <sge/once.hpp>
#include <boost/scoped_ptr.hpp>

namespace
{

boost::scoped_ptr<
	sge::log::logger
> instance;

void init();

}

sge::log::logger &
sge::log::global()
{
	init();
	return *instance;
}

namespace
{

void init()
{
	SGE_FUNCTION_ONCE
	instance.reset(
		new sge::log::logger(
			sge::log::level::debug,
			sge::cerr));
}

}
