/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SCENIC_RENDER_QUEUE_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_QUEUE_OBJECT_HPP_INCLUDED

#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/scenic/texture_manager_fwd.hpp>
#include <sge/scenic/render_context/base_fwd.hpp>
#include <sge/scenic/render_context/material/object.hpp>
#include <sge/scenic/render_queue/index_type.hpp>
#include <sge/scenic/render_queue/mesh.hpp>
#include <sge/scenic/render_queue/state_change_count.hpp>
#include <sge/scenic/scene/material/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace render_queue
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	object(
		sge::scenic::texture_manager &);

	void
	current_material(
		sge::scenic::scene::material::object const &);

	void
	current_vertex_buffer(
		sge::renderer::vertex_buffer &);

	void
	add_mesh(
		sge::renderer::matrix4 const &,
		sge::renderer::index_buffer &,
		sge::scenic::index_buffer_range const &);

	sge::scenic::render_queue::state_change_count const
	render(
		sge::scenic::render_context::base &);

	~object();
private:
	typedef
	std::vector<sge::scenic::render_context::material::object>
	material_sequence;

	typedef
	std::vector<sge::renderer::vertex_buffer*>
	vertex_buffer_sequence;

	typedef
	std::vector<sge::scenic::render_queue::mesh>
	mesh_sequence;

	sge::scenic::texture_manager &texture_manager_;
	material_sequence materials_;
	vertex_buffer_sequence vertex_buffers_;
	mesh_sequence meshes_;
	index_type current_material_;
	index_type current_vertex_buffer_;
};
}
}
}

#endif
