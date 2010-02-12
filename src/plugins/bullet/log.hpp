#ifndef SGE_BULLET_LOG_HPP_INCLUDED
#define SGE_BULLET_LOG_HPP_INCLUDED

/// NOTE: THIS IS INTENTIONAL! IF YOU INCLUDE log.hpp YOU WANT ALL THIS STUFF - ALWAYS!
#include <fcppt/log/headers.hpp>
#include <fcppt/log/parameters/inherited.hpp>

namespace sge
{
namespace bullet
{
fcppt::log::object &
log();
}
}

#endif
