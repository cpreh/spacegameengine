//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/type.hpp>


sge::opengl::texture::type
sge::opengl::texture::base::type() const
{
	return
		type_;
}

sge::opengl::texture::id
sge::opengl::texture::base::id() const
{
	return
		holder_.id();
}

sge::opengl::texture::base::~base()
= default;

sge::opengl::texture::base::base(
	sge::opengl::texture::type const _type
)
:
	type_(
		_type
	),
	holder_()
{
}
