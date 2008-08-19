#ifndef SGE_LOG_LEVEL_HPP_INCLUDED
#define SGE_LOG_LEVEL_HPP_INCLUDED

#include <boost/logging/detail/level.hpp> // TODO: we probably should not include detail headers

namespace sge
{
namespace log
{
namespace level
{
enum type {
  debug,
  info,
  warning,
  error,
  fatal
};
}//end level
boost::logging::level::type convert_level(level::type const);
}//end log
}//end sge

#endif
