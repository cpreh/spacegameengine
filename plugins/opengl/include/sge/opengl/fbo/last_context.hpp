//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_LAST_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_FBO_LAST_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/opengl/fbo/last_context_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class last_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		last_context
	);
public:
	last_context();

	~last_context()
	override;

	sge::opengl::fbo::id
	last_buffer() const;

	void
	last_buffer(
		sge::opengl::fbo::id
	);

	typedef void parameter;

	static sge::opengl::context::id const static_id;
private:
	sge::opengl::fbo::id last_buffer_;
};

}
}
}

#endif

