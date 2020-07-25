//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_SCENE_MESH_MATERIAL_TO_INDEX_BUFFER_RANGE_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MESH_MATERIAL_TO_INDEX_BUFFER_RANGE_HPP_INCLUDED

#include <sge/scenic/index_buffer_range.hpp>
#include <sge/scenic/scene/identifier.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
namespace mesh
{

using
material_to_index_buffer_range
=
std::map<
	sge::scenic::scene::identifier,
	sge::scenic::index_buffer_range
>;

}
}
}
}

#endif
