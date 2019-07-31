//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/fbo/bind.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/create_id.hpp>
#include <sge/opengl/fbo/delete_id.hpp>
#include <sge/opengl/fbo/id.hpp>
#include <sge/opengl/fbo/object.hpp>


sge::opengl::fbo::object::object(
	sge::opengl::fbo::config const &_context
)
:
	context_(
		_context
	),
	id_(
		sge::opengl::fbo::create_id(
			context_
		)
	)
{
}

sge::opengl::fbo::object::~object()
{
	sge::opengl::fbo::delete_id(
		context_,
		id_
	);
}

void
sge::opengl::fbo::object::bind() const
{
	sge::opengl::fbo::bind(
		context_,
		this->id()
	);
}

sge::opengl::fbo::id
sge::opengl::fbo::object::id() const
{
	return
		id_;
}
