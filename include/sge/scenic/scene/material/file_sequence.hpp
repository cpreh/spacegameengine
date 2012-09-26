#ifndef SGE_SCENIC_SCENE_MATERIAL_FILE_SEQUENCE_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_FILE_SEQUENCE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace scenic
{
namespace scene
{
namespace material
{
typedef
std::vector<boost::filesystem::path>
file_sequence;
}
}
}
}

#endif
