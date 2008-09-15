#ifndef SGE_OPENAL_ERROR_STRING_HPP_INCLUDED
#define SGE_OPENAL_ERROR_STRING_HPP_INCLUDED

#include <sge/file.hpp>
#include <sge/string.hpp>
#include <sge/stringize.hpp>

namespace sge
{
namespace openal
{
#define SGE_OPENAL_ERROR_CHECK error_check(SGE_FILE,SGE_STRINGIZE(__LINE__));
void error_check(string const &,string const &);
}
}

#endif
