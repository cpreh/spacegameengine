#ifndef SGE_LOG_GLOBAL_HPP_INCLUDED
#define SGE_LOG_GLOBAL_HPP_INCLUDED

#include "logger.hpp"
#include "level.hpp"
#include "../export.hpp"

namespace sge
{
namespace log
{

SGE_SYMBOL logger_stream& global(level::type lvl);

}
}

#endif
