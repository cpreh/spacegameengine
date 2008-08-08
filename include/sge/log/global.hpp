#ifndef SGE_LOG_GLOBAL_HPP_INCLUDED
#define SGE_LOG_GLOBAL_HPP_INCLUDED
#include "logger.hpp"
#include "level.hpp"

namespace sge
{
namespace log
{

logger_stream& global(const level::type lvl);

}
}

#endif
