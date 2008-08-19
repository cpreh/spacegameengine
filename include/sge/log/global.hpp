#ifndef SGE_LOG_GLOBAL_HPP_INCLUDED
#define SGE_LOG_GLOBAL_HPP_INCLUDED

#include "level.hpp"
#include "../export.hpp"
#include "../shared_ptr.hpp"
#include "../sstream.hpp"

namespace sge
{
namespace log
{

struct output_helper
{};

struct temporary_output {
  shared_ptr<
    ostringstream
  > os;
  SGE_SYMBOL temporary_output();
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

SGE_SYMBOL void global(level::type l, temporary_output t);

SGE_SYMBOL extern output_helper const _1;

}//end log
}//end sge

#endif
