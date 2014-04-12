/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_SCENIC_SCENE_MESH_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MESH_OBJECT_HPP_INCLUDED

#include <sge/model/obj/prototype_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/scenic/box.hpp>
#include <sge/scenic/scene/mesh/material_to_index_buffer_range.hpp>
#include <fcppt/math/box/object_impl.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
namespace mesh
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_SCENIC_SYMBOL
	object(
		sge::renderer::device::core &,
		sge::renderer::vertex::declaration &,
		sge::model::obj::prototype const &);

	SGE_SCENIC_SYMBOL
	sge::renderer::vertex::buffer &
	vertex_buffer();

	SGE_SCENIC_SYMBOL
	sge::renderer::index::buffer &
	index_buffer();

	SGE_SCENIC_SYMBOL
	sge::scenic::scene::mesh::material_to_index_buffer_range const &
	parts();

	SGE_SCENIC_SYMBOL
	sge::scenic::box const &
	bounding_box() const;

	SGE_SCENIC_SYMBOL
	~object();
private:
	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer_;
	sge::renderer::index::buffer_unique_ptr const index_buffer_;
	sge::scenic::scene::mesh::material_to_index_buffer_range parts_;
	sge::scenic::box bounding_box_;

	void
	fill_vertex_buffer(
		sge::model::obj::prototype const &);

	void
	fill_index_buffer(
		sge::model::obj::prototype const &);
};
}
}
}
}

#endif
