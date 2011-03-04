#ifndef SGE_IMAGE_OPTIONAL_PATH_HPP_INCLUDED
#define SGE_IMAGE_OPTIONAL_PATH_HPP_INCLUDED

#include <fcppt/filesystem/path.hpp>
#include <fcppt/optional_decl.hpp>

namespace sge
{
namespace image
{
typedef
fcppt::optional<fcppt::filesystem::path>
optional_path;
}
}

#endif
