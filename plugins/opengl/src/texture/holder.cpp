//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/holder.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/funcs/delete.hpp>
#include <sge/opengl/texture/funcs/gen.hpp>


sge::opengl::texture::holder::holder()
:
	id_(
		sge::opengl::texture::funcs::gen()
	)
{
}

sge::opengl::texture::holder::~holder()
{
	sge::opengl::texture::funcs::delete_(
		id_
	);
}

sge::opengl::texture::id
sge::opengl::texture::holder::id() const
{
	return
		id_;
}
