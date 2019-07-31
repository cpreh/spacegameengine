//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_TEMPORARY_BIND_HPP_INCLUDED
#define SGE_OPENGL_FBO_TEMPORARY_BIND_HPP_INCLUDED

#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/opengl/fbo/last_context_fwd.hpp>
#include <sge/opengl/fbo/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class temporary_bind
{
	FCPPT_NONCOPYABLE(
		temporary_bind
	);
public:
	temporary_bind(
		sge::opengl::fbo::config const &,
		sge::opengl::fbo::last_context &,
		sge::opengl::fbo::object const &
	);

	~temporary_bind();
private:
	sge::opengl::fbo::config const &context_;

	sge::opengl::fbo::last_context &last_context_;

	sge::opengl::fbo::id const last_buffer_;
};

}
}
}

#endif
