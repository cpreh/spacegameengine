//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_SCENE_FROM_BLENDER_FILE_HPP_INCLUDED
#define SGE_SCENIC_SCENE_FROM_BLENDER_FILE_HPP_INCLUDED

#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/scene/prototype_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::scenic::scene
{
SGE_SCENIC_DETAIL_SYMBOL
sge::scenic::scene::prototype_unique_ptr
from_blender_file(
	std::filesystem::path const &);
}

#endif
