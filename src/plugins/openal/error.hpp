#ifndef SGE_OPENAL_ERROR_STRING_HPP_INCLUDED
#define SGE_OPENAL_ERROR_STRING_HPP_INCLUDED

#include "openal.hpp"
#include <sge/file.hpp>
#include <sge/string.hpp>
#include <sge/stringize.hpp>

namespace sge
{
namespace openal
{
#define SGE_OPENAL_ERROR_CHECK error_check(SGE_FILE,SGE_STRINGIZE(__LINE__));
#define SGE_ALC_ERROR_CHECK(device) alc_error_check((device),SGE_FILE,SGE_STRINGIZE(__LINE__));
void error_check(string const &,string const &);
void alc_error_check(ALCdevice *,string const &,string const &);
}
}

#endif
