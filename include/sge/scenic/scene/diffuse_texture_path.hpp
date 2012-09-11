#ifndef SGE_SCENIC_SCENE_DIFFUSE_TEXTURE_PATH_HPP_INCLUDED
#define SGE_SCENIC_SCENE_DIFFUSE_TEXTURE_PATH_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace scenic
{
namespace scene
{
FCPPT_MAKE_STRONG_TYPEDEF(
	boost::filesystem::path,
	diffuse_texture_path);
}
}
}

#endif
