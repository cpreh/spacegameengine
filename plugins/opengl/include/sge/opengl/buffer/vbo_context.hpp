//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_BUFFER_VBO_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_VBO_CONTEXT_HPP_INCLUDED

#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/base_unique_ptr.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace buffer
{

class vbo_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		vbo_context
	);
public:
	typedef
	sge::opengl::context::object &
	parameter;

	explicit
	vbo_context(
		parameter
	);

	~vbo_context()
	override;

	sge::opengl::buffer::base &
	index_buffer() const;

	sge::opengl::buffer::base &
	vertex_buffer() const;

	static sge::opengl::context::id const static_id;
private:
	typedef
	std::array<
		sge::opengl::buffer::base_unique_ptr,
		2u
	>
	buffer_array;

	buffer_array const buffers_;
};

}
}
}

#endif
