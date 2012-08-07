#ifndef SGE_SCENIC_RENDER_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/scenic/render_context/index_type.hpp>
#include <sge/scenic/render_context/mesh.hpp>
#include <sge/scenic/render_context/state_change_count.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <vector>
#include <sge/renderer/material_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>

namespace sge
{
namespace scenic
{
namespace render_context
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	object();

	void
	current_material(
		sge::renderer::material const &);

	void
	current_vertex_buffer(
		sge::renderer::vertex_buffer &);

	void
	current_texture(
		fcppt::optional<sge::renderer::texture::planar &>);

	void
	add_mesh(
		sge::renderer::matrix4 const &,
		sge::renderer::index_buffer &,
		sge::model::obj::index_buffer_range const &);

	sge::scenic::render_context::state_change_count const
	render(
		sge::renderer::context::object &);

	~object();
private:
	typedef
	std::vector<sge::renderer::material const *>
	material_sequence;

	typedef
	std::vector<sge::renderer::vertex_buffer*>
	vertex_buffer_sequence;

	typedef
	std::vector<sge::renderer::texture::planar*>
	texture_sequence;

	typedef
	std::vector<sge::scenic::render_context::mesh>
	mesh_sequence;

	material_sequence materials_;
	vertex_buffer_sequence vertex_buffers_;
	texture_sequence textures_;
	mesh_sequence meshes_;
	index_type current_material_;
	index_type current_vertex_buffer_;
	index_type current_texture_;
};
}
}
}

#endif
