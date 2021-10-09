//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_SCENE_MATERIAL_FILE_SEQUENCE_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_FILE_SEQUENCE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <filesystem>
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
typedef std::vector<std::filesystem::path> file_sequence;
}
}
}
}

#endif
