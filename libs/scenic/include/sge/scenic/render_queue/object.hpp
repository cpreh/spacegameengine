//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_QUEUE_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_QUEUE_OBJECT_HPP_INCLUDED

#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/scenic/texture_manager_fwd.hpp>
#include <sge/scenic/render_context/base_fwd.hpp>
#include <sge/scenic/render_context/material/object.hpp>
#include <sge/scenic/render_queue/index_type.hpp>
#include <sge/scenic/render_queue/mesh.hpp>
#include <sge/scenic/render_queue/state_change_count.hpp>
#include <sge/scenic/scene/material/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object.hpp>
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
	explicit
	object(
		sge::scenic::texture_manager &);

	void
	current_material(
		sge::scenic::scene::material::object const &);

	void
	current_vertex_buffer(
		sge::renderer::vertex::buffer &);

	void
	add_mesh(
		sge::renderer::matrix4 const &,
		sge::renderer::index::buffer &,
		sge::scenic::index_buffer_range const &);

	sge::scenic::render_queue::state_change_count
	render(
		sge::scenic::render_context::base &);

	~object();
private:
	typedef
	std::vector<sge::scenic::render_context::material::object>
	material_sequence;

	typedef
	std::vector<sge::renderer::vertex::buffer*>
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
