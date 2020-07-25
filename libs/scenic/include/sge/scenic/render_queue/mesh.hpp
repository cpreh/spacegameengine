//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_RENDER_QUEUE_MESH_HPP_INCLUDED
#define SGE_SCENIC_RENDER_QUEUE_MESH_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/index/buffer_ref.hpp>
#include <sge/scenic/index_buffer_range.hpp>
#include <sge/scenic/render_queue/index_type.hpp>
#include <sge/scenic/render_queue/sort_index.hpp>


namespace sge
{
namespace scenic
{
namespace render_queue
{

class mesh
{
public:
	mesh(
		sge::scenic::render_queue::index_type material,
		sge::scenic::render_queue::index_type vertex_buffer,
		sge::renderer::matrix4,
		sge::renderer::index::buffer_ref,
		sge::scenic::index_buffer_range const &
	);

	[[nodiscard]]
	sge::scenic::render_queue::index_type
	material() const;

	[[nodiscard]]
	sge::scenic::render_queue::index_type
	vertex_buffer() const;

	[[nodiscard]]
	sge::renderer::matrix4 const &
	modelview() const;

	[[nodiscard]]
	sge::renderer::index::buffer &
	index_buffer() const;

	[[nodiscard]]
	sge::scenic::index_buffer_range const &
	index_buffer_range() const;

	[[nodiscard]]
	bool
	operator<(
		sge::scenic::render_queue::mesh const &_other
	) const
	{
		return
			sort_index_ < _other.sort_index_;
	}
private:
	sge::scenic::render_queue::index_type material_;
	sge::scenic::render_queue::index_type vertex_buffer_;
	sge::scenic::render_queue::sort_index sort_index_;
	sge::renderer::matrix4 modelview_;
	sge::renderer::index::buffer_ref index_buffer_;
	sge::scenic::index_buffer_range index_buffer_range_;
};

}
}
}

#endif
