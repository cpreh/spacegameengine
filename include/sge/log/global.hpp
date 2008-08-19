#ifndef SGE_LOG_GLOBAL_HPP_INCLUDED
#define SGE_LOG_GLOBAL_HPP_INCLUDED

#include "logger.hpp"
#include "level.hpp"
#include "../export.hpp"

namespace sge
{
namespace log
{

struct output_helper
{};

struct temporary_output {
  boost::shared_ptr<
    std::ostringstream
  > os;
  SGE_CLASS_SYMBOL temporary_output();
};

template<typename T>
temporary_output operator<<(output_helper const&, T const &t) {
  return temporary_output() << t;
}

template<typename T>
temporary_output operator<<(temporary_output const &s, T const &t) {
  temporary_output  n(s);
    *n.os << t;
  return n;
}

void SGE_SYMBOL log(level::type const l, temporary_output const t);

}//end log
}//end sge

#endif
