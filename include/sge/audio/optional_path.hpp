#ifndef SGE_AUDIO_OPTIONAL_PATH_HPP_INCLUDED
#define SGE_AUDIO_OPTIONAL_PATH_HPP_INCLUDED

#include <fcppt/optional_decl.hpp>
#include <fcppt/filesystem/path.hpp>

namespace sge
{
namespace audio
{
typedef
fcppt::optional<fcppt::filesystem::path>
optional_path;
}
}

#endif
