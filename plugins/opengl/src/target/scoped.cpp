//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/target/base.hpp>
#include <sge/opengl/target/scoped.hpp>


sge::opengl::target::scoped::scoped(
	sge::opengl::target::base &_target
)
:
	target_(
		_target
	)
{
	target_.bind();
}

sge::opengl::target::scoped::~scoped()
{
	target_.unbind();
}

sge::opengl::target::base &
sge::opengl::target::scoped::get() const
{
	return
		target_;
}
