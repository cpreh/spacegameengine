//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/postprocessing/fullscreen_quad.hpp>
#include <sge/postprocessing/vf/format.hpp>
#include <sge/postprocessing/vf/format_part.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <fcppt/math/vector/object_impl.hpp>


sge::postprocessing::fullscreen_quad::fullscreen_quad(
	sge::renderer::device::core &_renderer,
	sge::renderer::vertex::declaration &_vertex_declaration)
:
	renderer_(
		_renderer),
	vertex_declaration_(
		_vertex_declaration),
	vertex_buffer_(
		renderer_.create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				vertex_declaration_,
				sge::renderer::vf::dynamic::make_part_index
				<
					sge::postprocessing::vf::format,
					sge::postprocessing::vf::format_part
				>(),
				sge::renderer::vertex::count(
					4u),
				sge::renderer::resource_flags_field::null())))
{
	sge::renderer::vertex::scoped_lock vblock(
		*vertex_buffer_,
		sge::renderer::lock_mode::writeonly);

	sge::renderer::vf::view<sge::postprocessing::vf::format_part> vertices(
		vblock.value());

	sge::renderer::vf::view<sge::postprocessing::vf::format_part>::iterator vb_it(
		vertices.begin());

	// Left top
	vb_it->set<sge::postprocessing::vf::position>(
		sge::postprocessing::vf::position::packed_type(
			-1.0f,
			1.0f));

	(vb_it++)->set<sge::postprocessing::vf::texcoord>(
		sge::postprocessing::vf::texcoord::packed_type(
			0.0f,
			0.0f));

	// Left bottom
	vb_it->set<sge::postprocessing::vf::position>(
		sge::postprocessing::vf::position::packed_type(
			-1.0f,
			-1.0f));

	(vb_it++)->set<sge::postprocessing::vf::texcoord>(
		sge::postprocessing::vf::texcoord::packed_type(
			0.0f,
			1.0f));

	// Right top
	vb_it->set<sge::postprocessing::vf::position>(
		sge::postprocessing::vf::position::packed_type(
			1.0f,
			1.0f));

	(vb_it++)->set<sge::postprocessing::vf::texcoord>(
		sge::postprocessing::vf::texcoord::packed_type(
			1.0f,
			0.0f));

	// Right bottom
	vb_it->set<sge::postprocessing::vf::position>(
		sge::postprocessing::vf::position::packed_type(
			1.0f,
			-1.0f));

	(vb_it++)->set<sge::postprocessing::vf::texcoord>(
		sge::postprocessing::vf::texcoord::packed_type(
			1.0f,
			1.0f));

}

void
sge::postprocessing::fullscreen_quad::render(
	sge::renderer::context::core &_context)
{
	sge::renderer::vertex::scoped_declaration scoped_vd(
		_context,
		vertex_declaration_);

	sge::renderer::vertex::scoped_buffer scoped_vb(
		_context,
		*vertex_buffer_);

	_context.render_nonindexed(
		sge::renderer::vertex::first(
			0u),
		sge::renderer::vertex::count(
			vertex_buffer_->linear_size()),
		sge::renderer::primitive_type::triangle_strip);
}

sge::postprocessing::fullscreen_quad::~fullscreen_quad()
{
}

sge::renderer::vertex::declaration_unique_ptr
sge::postprocessing::fullscreen_quad::create_vertex_declaration(
	sge::renderer::device::core &_renderer)
{
	return
		_renderer.create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format
				<
					sge::postprocessing::vf::format
				>()));
}
