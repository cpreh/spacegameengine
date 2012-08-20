#include <sge/postprocessing/fullscreen_quad.hpp>
#include <sge/postprocessing/vf/format.hpp>
#include <sge/postprocessing/vf/format_part.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <fcppt/math/vector/object_impl.hpp>


sge::postprocessing::fullscreen_quad::fullscreen_quad(
	sge::renderer::device &_renderer,
	sge::renderer::vertex_declaration &_vertex_declaration)
:
	renderer_(
		_renderer),
	vertex_declaration_(
		_vertex_declaration),
	vertex_buffer_(
		renderer_.create_vertex_buffer(
			vertex_declaration_,
			sge::renderer::vf::dynamic::make_part_index
			<
				sge::postprocessing::vf::format,
				sge::postprocessing::vf::format_part
			>(),
			sge::renderer::vertex_count(
				4u),
			sge::renderer::resource_flags_field::null()))
{
	sge::renderer::scoped_vertex_lock vblock(
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
	sge::renderer::context::object &_context)
{
	sge::renderer::scoped_vertex_declaration scoped_vd(
		_context,
		vertex_declaration_);

	sge::renderer::scoped_vertex_buffer scoped_vb(
		_context,
		*vertex_buffer_);

	_context.render_nonindexed(
		sge::renderer::first_vertex(
			0u),
		sge::renderer::vertex_count(
			vertex_buffer_->size()),
		sge::renderer::primitive_type::triangle_strip);
}

sge::postprocessing::fullscreen_quad::~fullscreen_quad()
{
}

sge::renderer::vertex_declaration_unique_ptr
sge::postprocessing::fullscreen_quad::create_vertex_declaration(
	sge::renderer::device &_renderer)
{
	return
		_renderer.create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<sge::postprocessing::vf::format>());
}
