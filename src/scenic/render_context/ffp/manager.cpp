#include <sge/renderer/context/ffp.hpp>
#include <sge/scenic/render_context/ffp/manager.hpp>
#include <sge/scenic/render_context/ffp/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>


sge::scenic::render_context::ffp::manager::manager(
	sge::renderer::device::ffp &_renderer,
	sge::renderer::vertex_declaration &_vertex_declaration)
:
	renderer_(
		_renderer),
	vertex_declaration_(
		_vertex_declaration)
{
}

sge::scenic::render_context::base_unique_ptr
sge::scenic::render_context::ffp::manager::create_context(
	sge::renderer::context::core &_context)
{
	return
		sge::scenic::render_context::base_unique_ptr(
			fcppt::make_unique_ptr<sge::scenic::render_context::ffp::object>(
				fcppt::ref(
					*this),
				fcppt::ref(
					dynamic_cast<sge::renderer::context::ffp &>(
						_context))));
}

sge::scenic::render_context::ffp::manager::~manager()
{
}
