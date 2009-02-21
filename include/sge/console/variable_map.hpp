#ifndef SGE_CONSOLE_VARIABLE_MAP_HPP_INCLUDED
#define SGE_CONSOLE_VARIABLE_MAP_HPP_INCLUDED

#include <sge/console/var_base.hpp>
#include <sge/string.hpp>
#include <map>

namespace sge
{
namespace console
{
typedef std::map<string,var_base*> variable_map;
}
}

#endif
