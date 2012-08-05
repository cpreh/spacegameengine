#ifndef SGE_SCENIC_RENDER_CONTEXT_MESH_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_MESH_HPP_INCLUDED

#include <sge/scenic/render_context/index_type.hpp>
#include <sge/scenic/render_context/index_type.hpp>
#include <sge/scenic/render_context/sort_index.hpp>
#include <sge/renderer/index_buffer_fwd.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/model/obj/index_buffer_range.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class mesh
{
public:
	mesh(
		sge::scenic::render_context::index_type material,
		sge::scenic::render_context::index_type vertex_buffer,
		sge::scenic::render_context::index_type texture,
		sge::renderer::matrix4 const &,
		sge::renderer::index_buffer &,
		sge::model::obj::index_buffer_range const &);

	sge::scenic::render_context::index_type
	material() const;

	sge::scenic::render_context::index_type
	vertex_buffer() const;

	sge::scenic::render_context::index_type
	texture() const;

	sge::renderer::matrix4 const &
	modelview() const;

	sge::renderer::index_buffer &
	index_buffer() const;

	sge::model::obj::index_buffer_range const &
	index_buffer_range() const;

	bool
	operator<(
		sge::scenic::render_context::mesh const &_other) const
	{
		return
			sort_index_ < _other.sort_index_;
	}
private:
	sge::scenic::render_context::index_type material_;
	sge::scenic::render_context::index_type vertex_buffer_;
	sge::scenic::render_context::index_type texture_;
	sge::scenic::render_context::sort_index sort_index_;
	sge::renderer::matrix4 modelview_;
	sge::renderer::index_buffer *index_buffer_;
	sge::model::obj::index_buffer_range index_buffer_range_;
};

FCPPT_PP_POP_WARNING
}
}
}

#endif
