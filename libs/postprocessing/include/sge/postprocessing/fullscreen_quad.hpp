//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_POSTPROCESSING_FULLSCREEN_QUAD_HPP_INCLUDED
#define SGE_POSTPROCESSING_FULLSCREEN_QUAD_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::postprocessing
{

class fullscreen_quad
{
	FCPPT_NONMOVABLE(
		fullscreen_quad
	);
public:
	fullscreen_quad(
		sge::renderer::device::core_ref,
		sge::renderer::vertex::const_declaration_ref
	);

	void
	render(
		sge::renderer::context::core & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	~fullscreen_quad();

	static
	sge::renderer::vertex::declaration_unique_ptr
	create_vertex_declaration(
		sge::renderer::device::core_ref
	);
private:
	sge::renderer::vertex::const_declaration_ref const vertex_declaration_;

	sge::renderer::vertex::buffer_unique_ptr const vertex_buffer_;
};

}

#endif
