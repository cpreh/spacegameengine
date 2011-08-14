#ifndef SGE_MODEL_OBJ_VB_CONVERTER_CONVERT_HPP_INCLUDED
#define SGE_MODEL_OBJ_VB_CONVERTER_CONVERT_HPP_INCLUDED

#include <sge/model/obj/instance.hpp>
#include <sge/model/obj/vb_converter/detail/count_vertices.hpp>
#include <sge/model/obj/vb_converter/detail/convert_mesh.hpp>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>

namespace sge
{
namespace model
{
namespace obj
{
namespace vb_converter
{
template<typename VertexFormatPart,typename PositionMap>
renderer::vertex_buffer_ptr const
convert(
	renderer::device &_renderer,
	renderer::vertex_declaration const &_vd,
	obj::instance const &_model)
{
	renderer::vertex_buffer_ptr const result =
		_renderer.create_vertex_buffer(
			_vd,
			renderer::vf::dynamic::part_index(
				0u),
			detail::count_vertices<sge::renderer::size_type>(
				_model),
			sge::renderer::resource_flags::none);

	sge::renderer::scoped_vertex_lock const vblock(
		*result,
		sge::renderer::lock_mode::writeonly);

	typedef
	sge::renderer::vf::view<VertexFormatPart>
	vertex_part_view;

	typedef typename
	vertex_part_view::iterator
	vertex_iterator;

	vertex_part_view current_vertex_view(
		vblock.value());

	vertex_iterator current_vertex(
		current_vertex_view.begin());

	for(
		obj::mesh_sequence::const_iterator mesh_it =
			_model.meshes().begin();
		mesh_it != _model.meshes().end();
		++mesh_it)
		detail::convert_mesh<VertexFormatPart,PositionMap>(
			_model,
			current_vertex,
			*mesh_it);

	return result;
}
}
}
}
}

#endif
