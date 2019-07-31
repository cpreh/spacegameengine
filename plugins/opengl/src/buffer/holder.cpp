//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/holder.hpp>
#include <sge/opengl/buffer/id.hpp>


sge::opengl::buffer::holder::holder(
	sge::opengl::buffer::base &_base
)
:
	base_(
		_base
	),
	id_(
		_base.gen_buffer()
	)
{
}

sge::opengl::buffer::holder::~holder()
{
	base_.delete_buffer(
		id_
	);
}

sge::opengl::buffer::id
sge::opengl::buffer::holder::id() const
{
	return
		id_;
}
