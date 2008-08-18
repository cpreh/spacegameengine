#ifndef SGE_LOG_LOGGER_HPP_INCLUDED
#define SGE_LOG_LOGGER_HPP_INCLUDED

#include "../ostream.hpp"
#include <boost/logging/format/named_write.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{
namespace log
{

typedef boost::logging::named_logger< >::type logger_type;

}
}

#endif
