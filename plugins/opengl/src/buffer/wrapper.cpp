//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/wrapper.hpp>
#include <sge/renderer/opengl/buffer/id.hpp>


sge::opengl::buffer::wrapper::wrapper()
= default;

sge::opengl::buffer::wrapper::~wrapper()
= default;

sge::renderer::opengl::buffer::id
sge::opengl::buffer::wrapper::id() const
{
	return
		this->get().id();
}

bool
sge::opengl::buffer::wrapper::native() const
{
	return
		this->get().native();
}
