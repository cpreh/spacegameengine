//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_POSTPROCESSING_FULLSCREEN_QUAD_HPP_INCLUDED
#define SGE_POSTPROCESSING_FULLSCREEN_QUAD_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace postprocessing
{

class fullscreen_quad
{
	FCPPT_NONCOPYABLE(
		fullscreen_quad
	);
public:
	fullscreen_quad(
		sge::renderer::device::core &,
		sge::renderer::vertex::declaration &
	);

	void
	render(
		sge::renderer::context::core &
	);

	~fullscreen_quad();

	static
	sge::renderer::vertex::declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::device::core &
	);
private:
	sge::renderer::vertex::declaration &vertex_declaration_;

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer_;
};

}
}

#endif
