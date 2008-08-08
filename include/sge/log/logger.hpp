#ifndef SGE_LOG_LOGGER_HPP_INCLUDED
#define SGE_LOG_LOGGER_HPP_INCLUDED

#include "../ostream.hpp"
#include <boost/logging/format/named_write.hpp>

namespace sge
{
namespace log
{

typedef ostream logger_stream;

typedef boost::logging::named_logger< >::type logger_type;

}
}

#endif
