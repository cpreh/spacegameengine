//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_FBO_OBJECT_HPP_INCLUDED

#include <sge/opengl/fbo/const_config_ref.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/opengl/fbo/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::opengl::fbo
{

class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	explicit
	object(
		sge::opengl::fbo::const_config_ref
	);

	~object();

	void
	bind() const;

	[[nodiscard]]
	sge::opengl::fbo::id
	id() const;
private:
	sge::opengl::fbo::const_config_ref const context_;

	sge::opengl::fbo::id const id_;
};

}

#endif
