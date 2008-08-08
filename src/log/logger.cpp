#include <sge/log/logger.hpp>
#include <sge/log/level.hpp>

namespace sge
{

namespace log 
{
  BOOST_DEFINE_LOG(
    sge_logger, 
    logger_type
  )

  BOOST_DEFINE_LOG_FILTER(
    sge_log_level, 
    boost::logging::level::holder
  )
}

}

