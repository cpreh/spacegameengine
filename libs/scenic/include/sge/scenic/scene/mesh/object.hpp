//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_SCENE_MESH_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MESH_OBJECT_HPP_INCLUDED

#include <sge/model/obj/prototype_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/index/buffer_fwd.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/scenic/box.hpp>
#include <sge/scenic/scene/mesh/material_to_index_buffer_range.hpp>
#include <fcppt/noncopyable.hpp>
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
		object
	);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		sge::renderer::device::core_ref,
		sge::renderer::vertex::const_declaration_ref,
		sge::model::obj::prototype const &
	);

	SGE_SCENIC_DETAIL_SYMBOL
	object(
		object &&
	)
	noexcept;

	SGE_SCENIC_DETAIL_SYMBOL
	object &
	operator=(
		object &&
	)
	noexcept;

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::vertex::buffer &
	vertex_buffer();

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::renderer::index::buffer &
	index_buffer();

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::scene::mesh::material_to_index_buffer_range const &
	parts();

	[[nodiscard]]
	SGE_SCENIC_DETAIL_SYMBOL
	sge::scenic::box const &
	bounding_box() const;

	SGE_SCENIC_DETAIL_SYMBOL
	~object();
private:
	sge::renderer::vertex::buffer_unique_ptr vertex_buffer_;
	sge::renderer::index::buffer_unique_ptr index_buffer_;
	sge::scenic::scene::mesh::material_to_index_buffer_range parts_;
	sge::scenic::box bounding_box_;

	void
	fill_vertex_buffer(
		sge::model::obj::prototype const &
	);

	void
	fill_index_buffer(
		sge::model::obj::prototype const &
	);
};

}
}
}
}

#endif
