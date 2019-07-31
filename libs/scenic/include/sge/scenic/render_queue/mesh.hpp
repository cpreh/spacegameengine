//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_QUEUE_MESH_HPP_INCLUDED
#define SGE_SCENIC_RENDER_QUEUE_MESH_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/scenic/index_buffer_range.hpp>
#include <sge/scenic/render_queue/index_type.hpp>
#include <sge/scenic/render_queue/sort_index.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace scenic
{
namespace render_queue
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

class mesh
{
public:
	mesh(
		sge::scenic::render_queue::index_type material,
		sge::scenic::render_queue::index_type vertex_buffer,
		sge::renderer::matrix4 const &,
		sge::renderer::index::buffer &,
		sge::scenic::index_buffer_range const &);

	sge::scenic::render_queue::index_type
	material() const;

	sge::scenic::render_queue::index_type
	vertex_buffer() const;

	sge::renderer::matrix4 const &
	modelview() const;

	sge::renderer::index::buffer &
	index_buffer() const;

	sge::scenic::index_buffer_range const &
	index_buffer_range() const;

	bool
	operator<(
		sge::scenic::render_queue::mesh const &_other) const
	{
		return
			sort_index_ < _other.sort_index_;
	}
private:
	sge::scenic::render_queue::index_type material_;
	sge::scenic::render_queue::index_type vertex_buffer_;
	sge::scenic::render_queue::sort_index sort_index_;
	sge::renderer::matrix4 modelview_;
	sge::renderer::index::buffer *index_buffer_;
	sge::scenic::index_buffer_range index_buffer_range_;
};

FCPPT_PP_POP_WARNING
}
}
}

#endif
