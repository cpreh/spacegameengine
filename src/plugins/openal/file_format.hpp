#ifndef SGE_OPENAL_FILE_FORMAT_HPP_INCLUDED
#define SGE_OPENAL_FILE_FORMAT_HPP_INCLUDED

#include "openal.hpp"

namespace sge
{
namespace audio { class file; }

namespace openal
{
ALenum file_format(audio::file const &);
}
}

#endif
