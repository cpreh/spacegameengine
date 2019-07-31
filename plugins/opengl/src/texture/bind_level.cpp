//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/texture/active_level_fwd.hpp>
#include <sge/opengl/texture/bind_level.hpp>
#include <sge/opengl/texture/optional_id_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/funcs/bind.hpp>


void
sge::opengl::texture::bind_level(
	sge::opengl::texture::active_level const &,
	sge::opengl::texture::type const _type,
	sge::opengl::texture::optional_id const &_id
)
{
	sge::opengl::texture::funcs::bind(
		_type,
		_id
	);
}
