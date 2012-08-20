#ifndef SGE_POSTPROCESSING_FULLSCREEN_QUAD_HPP_INCLUDED
#define SGE_POSTPROCESSING_FULLSCREEN_QUAD_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/vertex_declaration_unique_ptr.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace postprocessing
{
class fullscreen_quad
{
FCPPT_NONCOPYABLE(
	fullscreen_quad);
public:
	fullscreen_quad(
		sge::renderer::device &,
		sge::renderer::vertex_declaration &);

	void
	render(
		sge::renderer::context::object &);

	~fullscreen_quad();

	static
	sge::renderer::vertex_declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::device &);
private:
	sge::renderer::device &renderer_;
	sge::renderer::vertex_declaration &vertex_declaration_;
	sge::renderer::vertex_buffer_scoped_ptr const vertex_buffer_;
};
}
}

#endif
