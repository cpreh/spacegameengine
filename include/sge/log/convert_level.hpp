#ifndef SGE_LOG_CONVERT_LEVEL_HPP_INCLUDED
#define SGE_LOG_CONVERT_LEVEL_HPP_INCLUDED

#include "level.hpp"
#include <boost/logging/detail/level.hpp> // TODO: we probably should not include detail headers

namespace sge
{
namespace log
{

boost::logging::level::type convert_level(level::type);

}
}

#endif
